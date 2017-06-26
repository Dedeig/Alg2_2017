#include "stdio.h"
#include "stdlib.h"
#include "math.h"

/*
	Programa feito para a disciplina SCC-0503 - Algoritmos e Estruturas de Dados 2
	Professor: Gustavo Batista
	Alunos:
		- Andrey Gobbo - 7152503
		- Gabriel Gonzales - 
		- Marcos Carvalho - 
	O programa recebe um arquivo.bmp como entrada e transforma em ASCII art.
	Uso: ./convertToAscii.c arquivo.bmp
*/

#define TRUE 1
#define FALSE 0
#define	MATRIXM 1 //Parâmetro 'M' definido na especificação para substituir os bits
#define MATRIXN 2 //Parâmetro 'N' definido na especificação para substituir os bits

//Struct com os dados do header da imagem - tipo, tamanho do arquivo e offset
typedef struct {
   unsigned short int type;                 /* Magic identifier                         */
   unsigned int size;                       /* Tamanho do arquivo, em Bytes             */
   unsigned short int reserved1, reserved2;
   unsigned int offset;                     /* Offset até o começo da imagem, em Bytes  */
} HEADER;

//struct com os metadados da imagem - tamanho do header, largura/altura da imagem, tipo de compressão, entre outros
typedef struct {
   unsigned int size;               /* Header size in bytes                  */
   int width,height;                /* Largura e altura da imagem, em pixels */
   unsigned short int planes;       /* Número de planos de cores             */
   unsigned short int bits;         /* Bits por pixel                        */
   unsigned int compression;        /* Tipo de compressão - será descartado  */
   unsigned int imagesize;          /* Tamanho da imagem - será descartado   */
   int xresolution,yresolution;     /* Pixels por metro - será descartado    */
   unsigned int ncolours;           /* Número de cores                       */
   unsigned int importantcolours;   /* Cores importantes                     */
} INFOHEADER;

typedef struct {
   unsigned char r,g,b,junk;
} COLOURINDEX;

/* Função lê um pedaço de tamanho 'int' (4 bits) no header do arquivo BMP*/
int ReadUInt(FILE *fptr,unsigned int *n,int swap)
{
   unsigned char *cptr,tmp;

   if (fread(n,4,1,fptr) != 1)
      return(FALSE);
   if (swap) {
      cptr = (unsigned char *)n;
      tmp = cptr[0];
      cptr[0] = cptr[3];
      cptr[3] = tmp;
      tmp = cptr[1];
      cptr[1] = cptr[2];
      cptr[2] = tmp;
   }
   return(TRUE);
}

/* Função lê um pedaço de tamanho 'short' (2 bits) no header do arquivo BMP*/
int ReadUShort(FILE *fptr,short unsigned *n,int swap)
{
   unsigned char *cptr,tmp;

   if (fread(n,2,1,fptr) != 1)
      return(FALSE);
	if (swap) {
   	cptr = (unsigned char *)n;
   	tmp = cptr[0];
   	cptr[0] = cptr[1];
   	cptr[1] =tmp;
	}
   return(TRUE);
}


int main(int argc,char **argv)
{
   int i,j,k, corPixel, intensidadeCor;
   int gotindex = FALSE;
   unsigned char grey,r,g,b, cbuf[4];
   HEADER header;
   INFOHEADER infoheader;
   COLOURINDEX colourindex[256];
   FILE *fptr;

   /* Checa o numero de argumentos ao rodar */
   if (argc < 2) {
      fprintf(stderr,"Usage: %s filename\n",argv[0]);
      exit(-1);
   }

   /* Abre o arquivo BMP */
   if ((fptr = fopen(argv[1],"r")) == NULL) {
      fprintf(stderr,"Não foi possível ler o arquivo BMP \"%s\"\n",argv[1]);
      exit(-1);
   }

   /* Ler e checar o header e os metadados da imagem */
   ReadUShort(fptr,&header.type,FALSE);
   ReadUInt(fptr,&header.size,FALSE);
   ReadUShort(fptr,&header.reserved1,FALSE);
   ReadUShort(fptr,&header.reserved2,FALSE);
   ReadUInt(fptr,&header.offset,FALSE);
   fprintf(stderr,"Offset para o começo dos pixels é %d bytes\n",header.offset);

   //Lê os metadados da imagem
   if (fread(&infoheader,sizeof(INFOHEADER),1,fptr) != 1) {
      fprintf(stderr,"Falha ao ler o HEADER de informações\n");
      exit(-1);
   }

   //Inicia a matriz de cores com o tamanho da imagem Largura x Altura com o valor 0
   int matrizCor[infoheader.height][infoheader.width];
   for(i = 0; i < infoheader.height; i++){
   		for (j = 0; j < infoheader.width; j++)
   		{
   			matrizCor[i][j] = 0;
   		}
   	}
   fprintf(stderr,"Tamanho da imagem = %d x %d\n",infoheader.width,infoheader.height);
   fprintf(stderr,"Bits por pixel %d\n",infoheader.bits);

   /* Read the lookup table if there is one */
   /*for (i=0;i<255;i++) {
      colourindex[i].r = rand() % 256;
      colourindex[i].g = rand() % 256;
      colourindex[i].b = rand() % 256;
      colourindex[i].junk = rand() % 256;
   }
   if (infoheader.ncolours > 0) {
      for (i=0;i<infoheader.ncolours;i++) {
         if (fread(&colourindex[i].b,sizeof(unsigned char),1,fptr) != 1) {
            fprintf(stderr,"Erro ao ler a imagem BMP\n");
            exit(-1);
         }
         if (fread(&colourindex[i].g,sizeof(unsigned char),1,fptr) != 1) {
            fprintf(stderr,"Erro ao ler a imagem BMP\n");
            exit(-1);
         }
         if (fread(&colourindex[i].r,sizeof(unsigned char),1,fptr) != 1) {
            fprintf(stderr,"Erro ao ler a imagem BMP\n");
            exit(-1);
         }
         if (fread(&colourindex[i].junk,sizeof(unsigned char),1,fptr) != 1) {
            fprintf(stderr,"Erro ao ler a imagem BMP\n");
            exit(-1);
         }
         fprintf(stderr,"%3d\t%3d\t%3d\t%3d\n",i,
            colourindex[i].r,colourindex[i].g,colourindex[i].b);
      }
      gotindex = TRUE;
   }*/

   /* Move a leitura do arquivo para o começo dos bits de pixel - SEEK_SET = header.offset */
   fseek(fptr,header.offset,SEEK_SET);

   /* Lê a imagem. Faz a leitura de maneira normal, a partir do canto esquerdo superior [0][0]*/
   for (j = 0;j < infoheader.height; j++) {
      for (i = 0;i < infoheader.width; i++) {

      //Faz a leitura da imagem, salvando em um buffer. A cor é definida pela media das cores RGB lidas
		fread(cbuf,1,infoheader.bits/8,fptr);
		corPixel = ((short)cbuf[2]+(short)cbuf[1]+(short)cbuf[0])/3;
      
      //Salva a media RGB na matriz de cores	
      matrizCor[j][i] = corPixel;
    	}
    }

   /*Faz o calculo da intesidade de pixel numa matriz MxN e imprime o caracter correspondente
      A leitura é feita a partir do canto esquerdo INFERIOR de acordo com a 'dica' da especificação. */
   for (i = (infoheader.height-1) ;i >= 0 ; i--) { //começa da ultima linha 
      for (j = 0;j < infoheader.width; j++) { //começa do canto esquerdo
      	intensidadeCor = (matrizCor[i][j]+matrizCor[i][j+1])/2;

 		   if((intensidadeCor >= 1) && (intensidadeCor <= 25))
 			  	printf("#");
 			else if((intensidadeCor >= 26) && (intensidadeCor <= 50))
 		      printf("$");
 			else if((intensidadeCor >= 51) && (intensidadeCor <= 75))
 			   printf("0");
 			else if((intensidadeCor >= 76) && (intensidadeCor <= 100))
 			   printf("=");
 			else if((intensidadeCor >= 101) && (intensidadeCor <= 125))
 			   printf("+");
 			else if((intensidadeCor >= 126) && (intensidadeCor <= 150))
 				printf("|");
 			else if((intensidadeCor >= 151) && (intensidadeCor <= 175))
 				printf("-");
 			else if((intensidadeCor >= 176) && (intensidadeCor <= 200))
 				printf("^");
 			else if((intensidadeCor >= 201) && (intensidadeCor <= 225))
 				printf(".");
 			else if((intensidadeCor >= 226) && (intensidadeCor <= 255))
 				printf(" ");
        	}
     	printf("\n");
   }
   printf("\n");

   fclose(fptr);
}
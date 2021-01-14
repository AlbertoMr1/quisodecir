#include <stdio.h>
#include <ctype.h>
#include <string.h>

//incializacion funciones
void QuitarCaracteres(char *palabra);
void Eliminar(char szPalabras[][TAMTOKEN],int &elementos,int iEstadisticas[]);
void Ordenar(char szPalabras[][TAMTOKEN],int elementos,int iEstadisticas[],int opcion);
int revertir(int posicion,char szPalabraLeidaCopia2[TAMTOKEN],char szPalabrasSugeridas[][TAMTOKEN],int jPalabra,int longitud);
//fin inicializacion funciones

void	Diccionario			(char *szNombre, 
char szPalabras[][TAMTOKEN], 
int iEstadisticas[], 
int &iNumElementos)
 {
    FILE* fp;
    char palabra[TAMTOKEN];
    iNumElementos=0;
    int i;

    fp=fopen(szNombre,"rb");

    while(feof(fp)==0)
    {
    fscanf(fp,"%s",palabra);
    QuitarCaracteres(palabra);
    strcpy(szPalabras[iNumElementos],palabra);
    iNumElementos++;
    }

    //printf("contador %i\n",iNumElementos);
    iNumElementos--;
    Eliminar(szPalabras,iNumElementos,iEstadisticas);
    //printf("contador %i\n",iNumElementos);
    Ordenar(szPalabras,iNumElementos,iEstadisticas,0);
 }

 void   ClonaPalabras(
    char *  szPalabraLeida,                     // Palabra a clonar
    char    szPalabrasSugeridas[][TAMTOKEN],    //Lista de palabras clonadas
    int &   iNumSugeridas)                      //Numero de elementos en la lista
{
    int longitud,posicion=0;
    int i,j,m,jPalabra=0,apuntador,jApuntador,contador;
    int posicion2=0;
    
    char letras[]={"abcdefghijklmnopqrstuvwxyz"};
    char letras2[]={"ñáéíóú"};
    
    //char szPalabraLeidaCopiaDef[TAMTOKEN];
    char szPalabraLeidaCopia[TAMTOKEN];
    char szPalabraLeidaCopia2[TAMTOKEN];
    char palabrafin[TAMTOKEN];
    char auxiliarPal[TAMTOKEN];
    char auxiliarPal2[TAMTOKEN];
    
    longitud=strlen(szPalabraLeida);
    
    for(i=0;i<longitud;i++)
    {
        for(j=0;j<strlen(letras);j++)
        {
            if(szPalabraLeida[i]==letras[j])
            {
                contador++;
            }
            else if(szPalabraLeida[i]==letras2[0])
            {
                posicion=i;
            }
        }
    }
    if(posicion!=0)
    {
        apuntador=0;
        for(i=0;i<longitud;i++)
        {
            if(szPalabraLeida[i]!=letras2[1])
            {
                palabrafin[apuntador]=szPalabraLeida[i];
                apuntador++;
            }
        }
        strcpy(szPalabraLeida,palabrafin);
        longitud--;
    }
    
    //inicio eliminacion
    for(i=0;i<longitud;i++)
    {
        apuntador=0;
        memset(palabrafin,0,50);
        
        for(j=0;j<longitud;j++)
        {
            if(i!=j)
            {
                palabrafin[apuntador]=szPalabraLeida[j];
                apuntador++;
            }
        }
        //printf("\t%s\n",palabrafin);
        //printf("longitud: %i\n",longitud);
        jPalabra=revertir(posicion,palabrafin,szPalabrasSugeridas,jPalabra,longitud);
    }
    //fin eliminacion
    
    //inicio intercambio
    for(j=1;j<longitud;j++)
    {
        strcpy(szPalabraLeidaCopia2,szPalabraLeida);
        strcpy(szPalabraLeidaCopia,szPalabraLeida);
        
        for(i=0;i<longitud-j;i++)
        {
            szPalabraLeidaCopia2[i+j]=szPalabraLeidaCopia2[i+(j-1)];
            szPalabraLeidaCopia2[i+(j-1)]=szPalabraLeidaCopia[i+j];
            
            jPalabra=revertir(posicion,szPalabraLeidaCopia2,szPalabrasSugeridas,jPalabra,longitud);
        }
    }
    //fin intercambio
    
    //inicio cambio de caracteres
    for(i=0;i<longitud;i++)
    {
        strcpy(szPalabraLeidaCopia,szPalabraLeida);
        
        for(j=0;j<strlen(letras);j++)
        {
            szPalabraLeidaCopia[i]=letras[j];
            jPalabra=revertir(posicion,szPalabraLeidaCopia,szPalabrasSugeridas,jPalabra,longitud);
            //strcpy(szPalabrasSugeridas[jPalabra],szPalabraLeidaCopia);
        }
    }
    
    for(i=0;i<longitud;i++)
    {
        strcpy(szPalabraLeidaCopia,szPalabraLeida);
        for(j=0;j<6;j++)
        {
            memset(auxiliarPal,0,50);
            memset(auxiliarPal2,0,50);
            
            apuntador=0;
            for(m=0;m<i;m++)
            {
                auxiliarPal[apuntador]=szPalabraLeidaCopia[m];
                apuntador++;
            }
            
            apuntador=0;
            for(m=i+1;m<longitud;m++)
            {
                auxiliarPal2[apuntador]=szPalabraLeidaCopia[m];
                apuntador++;
            }
            
            switch(j)
            {
                case 0:
                    strcat(auxiliarPal,"ñ");
                    strcat(auxiliarPal,auxiliarPal2);
                    break;
                case 1:
                    strcat(auxiliarPal,"á");
                    strcat(auxiliarPal,auxiliarPal2);
                    break;
                case 2:
                    strcat(auxiliarPal,"é");
                    strcat(auxiliarPal,auxiliarPal2);
                    break;
                case 3:
                    strcat(auxiliarPal,"í");
                    strcat(auxiliarPal,auxiliarPal2);
                    break;
                case 4:
                    strcat(auxiliarPal,"ó");
                    strcat(auxiliarPal,auxiliarPal2);
                    break;
                case 5:
                    strcat(auxiliarPal,"ú");
                    strcat(auxiliarPal,auxiliarPal2);
                    break;
            }
            jPalabra=revertir(posicion,auxiliarPal,szPalabrasSugeridas,jPalabra,longitud);
            //printf("aux: %s\n",auxiliarPal);
        }
    }
    //fin cambio de caracteres
    
    //inicio poner caracteres entre caracteres
    for(i=0;i<longitud+1;i++)
    {
        strcpy(szPalabraLeidaCopia,szPalabraLeida);
        for(j=0;j<strlen(letras);j++)
        {
            memset(auxiliarPal,0,50);
            memset(auxiliarPal2,0,50);
            
            apuntador=0;
            for(m=0;m<i;m++)
            {
                auxiliarPal[apuntador]=szPalabraLeidaCopia[m];
                apuntador++;
            }
            auxiliarPal[apuntador]=letras[j];
            
            apuntador=0;
            for(m=i;m<longitud;m++)
            {
                auxiliarPal2[apuntador]=szPalabraLeidaCopia[m];
                apuntador++;
            }
            
            strcat(auxiliarPal,auxiliarPal2);
            //printf("%s\n",auxiliar);
            jPalabra=revertir(posicion,auxiliarPal,szPalabrasSugeridas,jPalabra,longitud);
        }
    }
    //fin poner caracteres entre caracteres
    
    iNumSugeridas=jPalabra+1;
}
void    ListaCandidatas     (
    char    szPalabrasSugeridas[][TAMTOKEN],    //Lista de palabras clonadas
    int     iNumSugeridas,                      //Lista de palabras clonadas
    char    szPalabras[][TAMTOKEN],             //Lista de palabras del diccionario
    int     iEstadisticas[],                    //Lista de las frecuencias de las palabras
    int     iNumElementos,                      //Numero de elementos en el diccionario
    char    szListaFinal[][TAMTOKEN],           //Lista final de palabras a sugerir
    int     iPeso[],                            //Peso de las palabras en la lista final
    int &   iNumLista)                          //Numero de elementos en la szListaFinal
{
    int i,j,m;
    
    iNumLista=0;
    int iEstadisticas2[100];
    //printf("num sugeridas: %i\n",iNumSugeridas);
    //printf("num elementos: %i\n",iNumElementos);
    
    for(i=0;i<iNumSugeridas;i++)
    {
        for(j=0;j<iNumElementos;j++)
        {
            if(strcmp(szPalabrasSugeridas[i],szPalabras[j])==0)
            {
                strcpy(szListaFinal[iNumLista],szPalabras[j]);
                iPeso[iNumLista]=iEstadisticas[j];
                iNumLista++;
            }
        }
    }
    
    Eliminar(szListaFinal,iNumLista,iEstadisticas2);
    Ordenar(szListaFinal,iNumLista,iPeso,1);
}

//funciones
void QuitarCaracteres(char *palabra)
{
    //char auxiliar[strlen(palabra)];
    char simbolos[]=". ,;()";
    int i,j,apuntador=0;

    for(i=0;i<strlen(palabra);i++)
    {
        int anadir=1;
        for(j=0;j<strlen(simbolos);j++)
        {
            if(palabra[i]==simbolos[j])
            {
                anadir=0;
            }
        }
        if(anadir==1)
        {
            palabra[apuntador]=palabra[i];
            apuntador++;
        }
    }
    palabra[apuntador]=0;

    for(i=0;palabra[i]!='\0';i++)
    {
        palabra[i]=tolower(palabra[i]);
    }
}

void Eliminar(char szPalabras[][TAMTOKEN],int &elementos,int iEstadisticas[])
{
    int i,j,k;
    for(i=0;i<elementos;i++)
    {
        iEstadisticas[i]++;
    }

    for(i=0;i<elementos;i++)
    {
        for(j=i+1;j<elementos;j++)
        {
            if(strcmp(szPalabras[i],szPalabras[j])==0)
            {
                iEstadisticas[i] += 1;
                for(k=j;k<elementos;k++)
                {
                    strcpy(szPalabras[k],szPalabras[k+1]);
                }
                elementos--;
                j--;
            }
        }
    }    
    //iEstadisticas[elementos]-=1;
}

void Ordenar(char szPalabras[][TAMTOKEN],int elementos,int iEstadisticas[],int opcion)
{
    int i,j;
    char aux[50];
    int auxNum;

    if(opcion==0)
    {
        for(i=0;i<elementos;i++)
        {
            for(j=0;j<elementos-1;j++)
            {
                if(strcmp(szPalabras[j],szPalabras[j+1])>0)
                {
                    strcpy(aux,szPalabras[j]);
                    strcpy(szPalabras[j],szPalabras[j+1]);
                    strcpy(szPalabras[j+1],aux);

                    auxNum=iEstadisticas[j];
                    iEstadisticas[j]=iEstadisticas[j+1];
                    iEstadisticas[j+1]=auxNum;
                }
            }
        }
    }
    else if(opcion==1)
    {
        for(i=0;i<elementos;i++)
        {
            for(j=0;j<elementos-1;j++)
            {
                if(iEstadisticas[j]>iEstadisticas[j+1])
                {
                    auxNum=iEstadisticas[j];
                    iEstadisticas[j]=iEstadisticas[j+1];
                    iEstadisticas[j+1]=auxNum;

                    strcpy(aux,szPalabras[j]);
                    strcpy(szPalabras[j],szPalabras[j+1]);
                    strcpy(szPalabras[j+1],aux);
                }
            }
        }
    }
}

int revertir(int posicion,char szPalabraLeidaCopia2[TAMTOKEN],char szPalabrasSugeridas[][TAMTOKEN],int jPalabra,int longitud)
{
    int posicion2=-1;
    int apuntador=0;
    int k,h,m;
    
    char auxiliarPal[TAMTOKEN];
    char auxiliarPal2[TAMTOKEN];
    char letras2[]={"ñáéíóú"};
    
    if(posicion!=0)
    {
        for(k=0;k<longitud;k++)
        {
            if(szPalabraLeidaCopia2[k]==letras2[0])
            {
                posicion2=k;
            }
        }
        
        memset(auxiliarPal,0,50);
        memset(auxiliarPal2,0,50);
        
        apuntador=0;
        for(h=0;h<posicion2;h++)
        {
            auxiliarPal[apuntador]=szPalabraLeidaCopia2[h];
            apuntador++;
        }
        
        apuntador=0;
        for(m=posicion2+1;m<longitud;m++)
        {
            auxiliarPal2[apuntador]=szPalabraLeidaCopia2[m];
            apuntador++;
        }
        
        if(posicion2>=0)
        {
            strcat(auxiliarPal,"ñ");
            strcat(auxiliarPal,auxiliarPal2);
        }
        else
        {
            strcat(auxiliarPal,auxiliarPal2);
        }
        strcpy(szPalabrasSugeridas[jPalabra],auxiliarPal);
        //printf("aux: %s\n",szPalabrasSugeridas[jPalabra]);
        jPalabra++;
    }
    else
    {
        strcpy(szPalabrasSugeridas[jPalabra],szPalabraLeidaCopia2);
        //printf("%s\n",szPalabrasSugeridas[jPalabra]);
        jPalabra++;
    }
    
    return jPalabra;
}

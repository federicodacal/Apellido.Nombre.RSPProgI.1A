#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int id;
    char marca[20];
    int tipo;
    float peso;
}eVehiculo;

eVehiculo* vehiculo_new();
eVehiculo* vehiculo_newParams(int id, char* marca, int tipo, float peso);
void vehiculo_delete(eVehiculo* this);
int vehiculo_setId(eVehiculo* this, int id);
int vehiculo_setMarca(eVehiculo* this, char* marca);
int vehiculo_setTipo(eVehiculo* this, int tipo);
int vehiculo_setPeso(eVehiculo* this, float peso);
int esNombre(char* cadena,int longitud);
int saveAsBinary(char* path, eVehiculo* pVehiculo);
int saveAsText(char* path, eVehiculo* pVehiculo);
int vehiculo_getId(eVehiculo* this, int* id);
int vehiculo_getMarca(eVehiculo* this, char* marca);
int vehiculo_getTipo(eVehiculo* this, int* tipo);
int vehiculo_getPeso(eVehiculo* this, float* peso);

int main()
{
    eVehiculo* unVehiculo=vehiculo_newParams(1000,"Ford",2,400);

    if(!saveAsBinary("vehiculo.bin",unVehiculo)){
        printf("Archivo binario guardado correctamente\n");
    }

    if(!saveAsText("vehiculo.csv",unVehiculo)){
        printf("Archivo de texto guardado correctamente\n");
    }

    return 0;
}

eVehiculo* vehiculo_new()
{
    eVehiculo* newVehiculo=(eVehiculo*)malloc(sizeof(eVehiculo));

    if(newVehiculo!=NULL){
        newVehiculo->id=0;
        strcpy(newVehiculo->marca," ");
        newVehiculo->tipo=0;
        newVehiculo->peso=0;
    }
    return newVehiculo;
}

eVehiculo* vehiculo_newParams(int id, char* marca, int tipo, float peso)
{
    eVehiculo* newVehiculo=vehiculo_new();
    if(!(!vehiculo_setId(newVehiculo,id) &&
         !vehiculo_setMarca(newVehiculo,marca)&&
         !vehiculo_setTipo(newVehiculo,tipo) &&
         !vehiculo_setPeso(newVehiculo,peso))){
            vehiculo_delete(newVehiculo);
            newVehiculo=NULL;
        }
    return newVehiculo;
}

void vehiculo_delete(eVehiculo* this)
{
    if(this!=NULL){
        free(this);
    }
}

int vehiculo_setId(eVehiculo* this, int id)
{
    int response=-1;
    if(this!=NULL && id>=0){
        this->id=id;
        response=0;
    }
    return response;
}

int vehiculo_setMarca(eVehiculo* this, char* marca)
{
    int response=-1;
    if(this!=NULL && marca!=NULL){
        if(esNombre(marca,128)){
            strncpy(this->marca,marca,128);
            response=0;
        }
    }
    return response;
}

int vehiculo_setTipo(eVehiculo* this, int tipo)
{
    int response=-1;
    if(this!=NULL && tipo>=0){
        this->tipo=tipo;
        response=0;
    }
    return response;
}

int vehiculo_setPeso(eVehiculo* this, float peso)
{
    int response=-1;
    if(this!=NULL && peso>=0){
        this->peso=peso;
        response=0;
    }
    return response;
}

int esNombre(char* cadena,int longitud)
{
	int response=1;
	if(cadena != NULL && longitud > 0){
		for(int i=0 ; cadena[i] != '\0' && i < longitud; i++){
			if((cadena[i] < 'A' || cadena[i] > 'Z' ) && (cadena[i] < 'a' || cadena[i] > 'z') && cadena[i]!=' '){
				response=0;
				break;
			}
		}
	}
	return response;
}

int vehiculo_getId(eVehiculo* this, int* id)
{
    int response=-1;
    if(this!=NULL && id!=NULL){
        *id=this->id;
        response=0;
    }
    return response;
}

int vehiculo_getMarca(eVehiculo* this, char* marca)
{
    int response=-1;
    if(this!=NULL && marca!=NULL){
        strncpy(marca,this->marca,128);
        response=0;
    }
    return response;
}

int vehiculo_getTipo(eVehiculo* this, int* tipo)
{
    int response=-1;
    if(this!=NULL && tipo!=NULL){
        *tipo=this->tipo;
        response=0;
    }
    return response;
}

int vehiculo_getPeso(eVehiculo* this, float* peso)
{
    int response=-1;
    if(this!=NULL && peso!=NULL){
        *peso=this->peso;
        response=0;
    }
    return response;
}

int saveAsBinary(char* path, eVehiculo* pVehiculo)
{
    int response=-1;
    FILE* f;

    if(path!=NULL && pVehiculo!=NULL){
        f=fopen(path,"wb");
        if(f==NULL){
            printf("Ocurrio un problema\n");
        }
        else{
            fwrite(pVehiculo,sizeof(pVehiculo),1,f);
            response=0;
        }

        fclose(f);

    }
    return response;
}

//int saveAsText(char* path, eVehiculo* pVehiculo)
//{
//    int response=-1;
//    int auxId;
//    char auxMarca[20];
//    int auxTipo;
//    float auxPeso;
//
//    FILE* f;
//
//    if(path!=NULL && pVehiculo!=NULL){
//        f=fopen(path,"w");
//        if(f==NULL){
//            printf("Ocurrio un problema\n");
//        }
//        else{
//            if(!vehiculo_getId(pVehiculo,&auxId) &&
//               !vehiculo_getMarca(pVehiculo,auxMarca) &&
//               !vehiculo_getTipo(pVehiculo,&auxTipo) &&
//               !vehiculo_getPeso(pVehiculo,&auxPeso)){
//                 fprintf(f,"%d,%s,%d,%f\n",auxId,auxMarca,auxTipo,auxPeso);
//                 response=0;
//               }
//        }
//        fclose(f);
//    }
//    return response;
//}

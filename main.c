#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct error{
        int num; 
        char *msg;
}error;
error * new_error(int num, char *msg){
        error *err=malloc(sizeof(error));

        err->num=num;
        err->msg=msg;
        return err;
}

typedef struct panel{
        char *text;
        char *path;
        size_t size;
        error *err;
}panel;

panel *new_panel(char *path){
        panel *p=malloc(sizeof(panel));
        p->text=NULL;
        p->path=path;
        p->size=0;
        p->err=NULL;

        return p;
}
void nulled(void *p){
        if(p!=NULL){
                free(p);
                p=NULL;
        }
}
void load_text(panel *p){
        FILE *f=NULL;
        size_t size=0;
        size_t nsize=0;

        f=fopen(p->path, "r");
        if(f==NULL){
                p->err=new_error(1,"Can't open file!");
                return;
        }
        fseek(f, 0, SEEK_END); 
        size = ftell(f);
        fseek(f, 0, SEEK_SET);
        if(p->text!=NULL){
                p->err=new_error(2,"Text already loaded or not init propertly.");
                return; 
        }
        p->text=malloc((size+1)*sizeof(char));
        if(p->text==NULL){
                p->err=new_error(3,"Need more memory/file to big.");
                fclose(f);
                return;
        }
        p->text[size]='\0';
        if( (nsize= fread(p->text,sizeof(char), size, f) <=0 )){
                p->err=new_error(4, "Empty file or even worst.");
        }
        p->size=size;
        fclose(f);
        return;

}

void insert_text(panel *p, size_t cursor, char *text, size_t size){
        
        char *new_text=NULL; 
        if(cursor>p->size){
                p->err=new_error(6,"Cursor bigger then size.");
                return;
        }
        new_text = malloc((p->size+size)*sizeof(char));
        if(new_text==NULL){
                p->err=new_error(5,"Need more memory/file to big.");
                return;
        }
        new_text[0]='\0';
        memcpy(new_text, p->text,cursor);/*head*/
        new_text+=cursor;
        p->text+=cursor;
        
        memcpy(new_text, text, size);/*mid*/
        new_text+=size;
        
        memcpy(new_text, p->text,p->size-cursor);/*tail*/
        new_text-=(size+cursor);/*back to */
        p->text-=cursor;        /*begin*/
        
        p->size+=size;          /*swap nad free*/
        nulled(p->text);
        p->text=new_text;
        /*printf("nt:%s\n---------\n",new_text);*/
}
char* cuted_text(panel *p, size_t cursor, size_t size){
        char *new_text=NULL;
        char *cut_text=NULL;
        if(size > p->size){
                p->err=new_error(7,"To much char ro delete.");
                return NULL;
        }
        if(cursor>p->size){
                p->err=new_error(8,"Cursor bigger then size.");
                return NULL;
        }
        cut_text=malloc((size)*sizeof(char));
        if(cut_text==NULL){
                p->err=new_error(10,"Need more memory/file to big.");
                return NULL;
        }
        cut_text[0]='\0';
        new_text = malloc((p->size-size)*sizeof(char));
        if(new_text==NULL){
                p->err=new_error(9,"Need more memory/file to big.");
                return NULL;
        }
        new_text[0]='\0';
        memcpy(new_text, p->text,cursor);/*head*/
        new_text+=cursor;
        p->text+=cursor;
        
        memcpy(cut_text, p->text, size);/*mid*/
        p->text+=size;
        
        memcpy(new_text, p->text,p->size-cursor);/*tail*/
        new_text-=cursor;/*back to */
        p->text-=(size+cursor);        /*begin*/
        
        p->size-=size;          /*swap nad free*/
        nulled(p->text);
        p->text=new_text;
        
        return cut_text;
}
void save(){
}
char* print(panel *p){
        if(p->text!=NULL){
                return p->text;
        }else{
                if(p->err){
                        return p->err->msg;
                }else{
                        return "";
                }
        }
}
int main(int argc, char **argv)
{
        panel *p=new_panel("/home/seba/Code/text_processer/text.txt");
        load_text(p);
        insert_text(p, 5, "Kuuureaaa\n", 10);
        printf("cuted: %s\n",cuted_text(p, 0,5));
        printf("%s\n", print(p));
        if(p->err!=NULL){
                printf("err: %s\n",p->err->msg);
        }
        nulled(p);
	return 0;
}

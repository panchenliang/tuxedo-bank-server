#include <mysql.h>
#include <stdio.h>
#include <string.h>

int main(int argc,char *argv){
	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *query;
	int t,r;
	mysql_init(&mysql);
	if(!mysql_real_connect(&mysql,"localhost","root","akira86","tuxedo",0,NULL,0))
	{
	printf("connect database error");
	}
	else{
	printf("Connected...\n");
	}
	query="select * from T_USER";
	t=mysql_real_query(&mysql,query,(unsigned int)strlen(query));
	if(t){
	printf("Error making query:%s\n",mysql_error(&mysql));
	}
	else{
	res=mysql_store_result(&mysql);
		while(row=mysql_fetch_row(res)){
		for(t=0;t<mysql_num_fields(res);t++){
			printf("%s",row[t]);
			}
		printf("\n");
		}
	
	}
	mysql_close(&mysql);
return 1;
}


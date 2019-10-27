// README
// sudo apt-get install libmysqlclient-dev
// gcc version.c -o version  `mysql_config --cflags --libs`
// CREATE USER user12@localhost IDENTIFIED BY '34klq*';
// GRANT ALL ON testdb.* to user12@localhost;
//







#include <iostream>
#include <my_global.h>
#include <mysql.h>

using namespace std;


void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}



int main(int argc, char const *argv[])
{
  MYSQL *con = mysql_init(NULL);

  if (con == NULL)
  {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }

  if (mysql_real_connect(con, "localhost", "user12", "34klq*", "nimbus", 0, NULL, 0) == NULL)
  {
      finish_with_error(con);
  }

  if (mysql_query(con, "SELECT Username FROM UserDB"))
  {
      finish_with_error(con);
  }

  MYSQL_RES *result = mysql_store_result(con);

  if (result == NULL)
  {
      finish_with_error(con);
  }

  int num_fields = mysql_num_fields(result);

  MYSQL_ROW row;

  while ((row = mysql_fetch_row(result)))
  {
      for(int i = 0; i < num_fields; i++)
      {
          printf("%s ", row[i] ? row[i] : "NULL");
      }
          printf("\n");
  }






  mysql_free_result(result);
  mysql_close(con);

  exit(0);
}

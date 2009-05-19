CFG=mysql_config

sh -c "gcc -o testsql `$CFG --cflags` testsql.c `$CFG --libs`"

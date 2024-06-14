import mysql.connector
from mysql.connector import errorcode


def create_connection():
    try:
        cnx = mysql.connector.connect(
            user="root", password="2539", database="2024-recit8-2"
        )
        print("Connection established with the database")
        return cnx
    except mysql.connector.Error as err:
        if err.errno == errorcode.ER_ACCESS_DENIED_ERROR:
            print("Something is wrong with your user name or password")
        elif err.errno == errorcode.ER_BAD_DB_ERROR:
            print("Database does not exist")
        else:
            print(err)
        cnx.close()
        return None

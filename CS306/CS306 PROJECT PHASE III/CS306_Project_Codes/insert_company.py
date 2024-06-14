import mysql.connector
from connect import create_connection

def insert_company(symbol, name, shares):
    conn = create_connection()
    if conn:
        try:
            cursor = conn.cursor()
            sql = "INSERT INTO Company (symbol, name, outstanding_shares) VALUES (%s, %s, %s)"
            cursor.execute(sql, (symbol, name, shares))
            conn.commit()
            print(f"Inserted company: {symbol}")
        except mysql.connector.Error as err:
            print(f"Error: {err}")
        finally:
            conn.close()


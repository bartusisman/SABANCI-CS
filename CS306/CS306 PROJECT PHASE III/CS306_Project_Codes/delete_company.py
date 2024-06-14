import mysql.connector
from connect import create_connection

def delete_company(symbol):
    conn = create_connection()
    if conn:
        try:
            cursor = conn.cursor()
            sql = "DELETE FROM Company WHERE symbol = %s"
            cursor.execute(sql, (symbol,))
            conn.commit()
            print(f"Deleted company: {symbol}")
        except mysql.connector.Error as err:
            print(f"Error: {err}")
        finally:
            conn.close()



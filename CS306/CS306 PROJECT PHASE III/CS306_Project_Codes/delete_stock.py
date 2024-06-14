import mysql.connector
from connect import create_connection

def delete_stock(symbol, date):
    conn = create_connection()
    if conn:
        try:
            cursor = conn.cursor()
            sql = "DELETE FROM Stock WHERE symbol = %s AND date = %s"
            cursor.execute(sql, (symbol, date))
            conn.commit()
            print(f"Deleted stock record for: {symbol} on {date}")
        except mysql.connector.Error as err:
            print(f"Error: {err}")
        finally:
            conn.close()



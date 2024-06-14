import mysql.connector
from connect import create_connection

def insert_stock(symbol, date, highest, lowest, opening, closing, volume):
    conn = create_connection()
    if conn:
        try:
            cursor = conn.cursor()
            sql = "INSERT INTO Stock (symbol, date, highest, lowest, opening, closing, volume) VALUES (%s, %s, %s, %s, %s, %s, %s)"
            cursor.execute(sql, (symbol, date, highest, lowest, opening, closing, volume))
            conn.commit()
            print(f"Inserted stock record for: {symbol} on {date}")
        except mysql.connector.Error as err:
            print(f"Error: {err}")
        finally:
            conn.close()


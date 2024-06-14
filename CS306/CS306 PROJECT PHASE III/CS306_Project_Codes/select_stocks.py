import mysql.connector
from connect import create_connection

def select_stocks(limit=10):
    conn = create_connection()
    if conn:
        try:
            cursor = conn.cursor()
            sql = "SELECT * FROM Stock LIMIT %s"
            cursor.execute(sql, (limit,))
            records = cursor.fetchall()
            for record in records:
                print(record)
        except mysql.connector.Error as err:
            print(f"Error: {err}")
        finally:
            conn.close()


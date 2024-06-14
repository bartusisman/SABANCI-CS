import mysql.connector
from connect import create_connection

def update_company(symbol, name=None, shares=None):
    conn = create_connection()
    if conn:
        try:
            cursor = conn.cursor()
            updates = []
            params = []
            if name:
                updates.append("name = %s")
                params.append(name)
            if shares:
                updates.append("outstanding_shares = %s")
                params.append(shares)
            params.append(symbol)
            sql = f"UPDATE Company SET {', '.join(updates)} WHERE symbol = %s"
            cursor.execute(sql, params)
            conn.commit()
            print(f"Updated company: {symbol}")
        except mysql.connector.Error as err:
            print(f"Error: {err}")
        finally:
            conn.close()


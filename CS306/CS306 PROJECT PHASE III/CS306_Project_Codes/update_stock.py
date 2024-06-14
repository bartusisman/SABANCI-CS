import mysql.connector
from connect import create_connection

def update_stock(symbol, date, highest=None, lowest=None, opening=None, closing=None, volume=None):
    conn = create_connection()
    if conn:
        try:
            cursor = conn.cursor()
            updates = []
            params = []
            if highest:
                updates.append("highest = %s")
                params.append(highest)
            if lowest:
                updates.append("lowest = %s")
                params.append(lowest)
            if opening:
                updates.append("opening = %s")
                params.append(opening)
            if closing:
                updates.append("closing = %s")
                params.append(closing)
            if volume:
                updates.append("volume = %s")
                params.append(volume)
            params.extend([symbol, date])
            sql = f"UPDATE Stock SET {', '.join(updates)} WHERE symbol = %s AND date = %s"
            cursor.execute(sql, params)
            conn.commit()
            print(f"Updated stock record for: {symbol} on {date}")
        except mysql.connector.Error as err:
            print(f"Error: {err}")
        finally:
            conn.close()



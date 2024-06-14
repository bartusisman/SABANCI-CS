import mysql.connector
from connect import create_connection
from cursor_utils import *

cnx = create_connection()
cursor = cnx.cursor()

query = """DELETE FROM countries WHERE iso_code = 'GBR'"""
cursor.execute(query)
cnx.commit()
print("Query executed successfully")

filters = [{"field": "iso_code", "value": "TUR", "operator": "="}]

delete_operation(cursor=cursor, table_name="countries", filters=filters)
cnx.commit()

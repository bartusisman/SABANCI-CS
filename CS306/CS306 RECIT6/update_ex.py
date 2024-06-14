import _mysql_connector
from connect import create_connection
from cursor_utils import *

cnx = create_connection()

cursor = cnx.cursor()

# If you want to execute a query, you can do it directly by writing the whole query

query = """UPDATE countries SET country_name = 'Turkie' WHERE iso_code = 'TUR'"""
cursor.execute(query)
cnx.commit()

# Or again you can use utils

values = {"country_name": "Turkie", "population": 40000000}
filters = [{"field": "iso_code", "operator": "=", "value": "SPN"}]

update_operation(cursor=cursor, table_name="countries", values=values, filters=filters)

cnx.commit()

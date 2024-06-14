from pymongo import MongoClient

def get_database():
    CONNECTION_STRING = "mongodb+srv://bartu:12345@cluster0.mvtl2ui.mongodb.net/?retryWrites=true&w=majority&appName=Cluster0"
    client = MongoClient(CONNECTION_STRING)
    return client['SU_Stock']

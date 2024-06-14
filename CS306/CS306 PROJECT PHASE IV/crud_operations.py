def create_collection(db, name):
    collection = db[name]
    return collection

def read_all_data(collection):
    data = collection.find()
    for item in data:
        print(item)

def read_filtered_data(collection, query):
    data = collection.find(query)
    for item in data:
        print(item)

def insert_data(collection, data):
    collection.insert_one(data)
    print("Data inserted successfully.")

def delete_data(collection, query):
    collection.delete_one(query)
    print("Data deleted successfully.")

def update_data(collection, query, new_values):
    collection.update_one(query, {"$set": new_values})
    print("Data updated successfully.")

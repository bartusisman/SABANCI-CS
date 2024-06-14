from connection import get_database
from crud_operations import create_collection, read_all_data, read_filtered_data, insert_data, delete_data, update_data

def list_collections(db):
    collections = db.list_collection_names()
    if not collections:
        print("The database has no collections.")
    else:
        for i, collection in enumerate(collections, 1):
            print(f"{i} - {collection}")
    return collections

def select_collection(db):
    collections = list_collections(db)
    if not collections:
        return None
    while True:
        try:
            choice = int(input("Please select the collection number: "))
            if 1 <= choice <= len(collections):
                return collections[choice - 1]
            else:
                print("Invalid selection. Please try again.")
        except ValueError:
            print("Invalid input. Please enter a number.")

def main():
    db = get_database()
    
    while True:
        print("Please pick an option:")
        print("1 - Create a collection")
        print("2 - Read all data in a collection")
        print("3 - Read filtered data in a collection")
        print("4 - Insert data")
        print("5 - Delete data")
        print("6 - Update data")
        option = input("Selected option: ")

        if option == "1":
            name = input("Enter collection name: ")
            collection = create_collection(db, name)
            # Insert a dummy document to ensure the collection is created
            collection.insert_one({"dummy_key": "dummy_value"})
            print(f"Collection '{name}' created and dummy document inserted.")
        elif option in ["2", "3", "4", "5", "6"]:
            collection_name = select_collection(db)
            if collection_name is None:
                print("Returning to main menu.")
                continue
            collection = db[collection_name]
            
            if option == "2":
                read_all_data(collection)
            elif option == "3":
                query = eval(input("Enter query as a dictionary: "))
                read_filtered_data(collection, query)
            elif option == "4":
                data = eval(input("Enter data as a dictionary: "))
                insert_data(collection, data)
            elif option == "5":
                query = eval(input("Enter query as a dictionary: "))
                delete_data(collection, query)
            elif option == "6":
                query = eval(input("Enter query as a dictionary: "))
                new_values = eval(input("Enter new values as a dictionary: "))
                update_data(collection, query, new_values)
        else:
            print("Invalid option, please try again.")

if __name__ == "__main__":
    main()

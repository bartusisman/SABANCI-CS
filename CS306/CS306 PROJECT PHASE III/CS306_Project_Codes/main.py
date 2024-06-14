from insert_company import insert_company
from insert_stock import insert_stock
from select_companies import select_companies
from select_stocks import select_stocks
from delete_company import delete_company
from delete_stock import delete_stock
from update_company import update_company
from update_stock import update_stock

def main():

    print("Before Insert Operations:")
    print("Company Table:")
    select_companies()
    print("Stock Table:")
    select_stocks()

    insert_company('NFLX', 'Netflix Inc.', 450000000)
    insert_company('DIS', 'Walt Disney Co.', 1820000000)

    insert_stock('NFLX', '2023-10-01', 490.25, 485.30, 487.00, 489.55, 1000000)
    insert_stock('DIS', '2023-10-01', 135.50, 130.75, 132.00, 134.50, 5000000)

    print("\nAfter Insert Operations:")
    print("Company Table:")
    select_companies()
    print("Stock Table:")
    select_stocks()

    print("\nBefore Update Operations:")
    print("Company Table:")
    select_companies()
    print("Stock Table:")
    select_stocks()

    # Update records in Company table
    update_company('NFLX', name='Netflix Corporation', shares=460000000)

    # Update records in Stock table
    update_stock('NFLX', '2023-10-01', closing=490.00)

    print("\nAfter Update Operations:")
    print("Company Table:")
    select_companies()
    print("Stock Table:")
    select_stocks()

    print("\nBefore Delete Operations:")
    print("Company Table:")
    select_companies()
    print("Stock Table:")
    select_stocks()

    # Delete records in Stock table first
    delete_stock('NFLX', '2023-10-01')

    # Delete records in Company table
    delete_company('NFLX')

    print("\nAfter Delete Operations:")
    print("Company Table:")
    select_companies()
    print("Stock Table:")
    select_stocks()

if __name__ == "__main__":
    main()

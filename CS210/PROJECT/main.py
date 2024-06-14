import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error
import matplotlib.pyplot as plt

# Load the datasets
stock_market_data_path = r'C:\Users\zirve\Masaüstü\SABANCI CS\CS210\PROJECT\Stock Market Dataset.csv'
stock_market_data = pd.read_csv(stock_market_data_path)

# Convert 'S&P_500_Price' to numeric, removing commas and converting to float
stock_market_data['S&P_500_Price'] = pd.to_numeric(stock_market_data['S&P_500_Price'].str.replace(',', ''), errors='coerce')

# Drop rows with any missing values to clean up the data
stock_market_data.dropna(inplace=True)

# Extracting the independent variable (Natural_Gas_Price) and the dependent variable (S&P_500_Price)
X = stock_market_data[['Natural_Gas_Price']]  # Independent variable
y = stock_market_data['S&P_500_Price']  # Dependent variable

# Splitting the data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Initialize and train the linear regression model
model = LinearRegression()
model.fit(X_train, y_train)

# Predicting the test set results
y_pred = model.predict(X_test)

# Evaluating the model
mse = mean_squared_error(y_test, y_pred)
print(f"Mean Squared Error: {mse}")

# Plotting the results
plt.scatter(X_test, y_test, color='red', label='Actual S&P 500 Price')
plt.plot(X_test, y_pred, color='blue', label='Predicted S&P 500 Price')
plt.title('Natural Gas Price vs S&P 500 Price Prediction')
plt.xlabel('Natural Gas Price')
plt.ylabel('S&P 500 Price')
plt.legend()
plt.show()

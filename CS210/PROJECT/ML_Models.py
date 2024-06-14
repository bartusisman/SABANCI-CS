# Import necessary libraries
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestRegressor
from sklearn.svm import SVR
from sklearn.metrics import mean_squared_error, r2_score

# Load datasets with specified encoding
stock_market_df = pd.read_csv('Stock Market Dataset.csv', encoding='ISO-8859-1')
world_gdp_df = pd.read_csv('world_gdp_data.csv', encoding='ISO-8859-1')

# Strip any potential whitespace from the column names
stock_market_df.columns = stock_market_df.columns.str.strip()
world_gdp_df.columns = world_gdp_df.columns.str.strip()

# Strip any potential whitespace from the column names
stock_market_df.columns = stock_market_df.columns.str.strip()
world_gdp_df.columns = world_gdp_df.columns.str.strip()

# Data preparation
# Convert 'Date' column to datetime with dayfirst=True to handle mixed date formats
def parse_dates(date):
    try:
        return pd.to_datetime(date, dayfirst=True)
    except ValueError:
        return pd.to_datetime(date, format='%d-%m-%Y')

stock_market_df['Date'] = stock_market_df['Date'].apply(parse_dates)

# Convert 'S&P_500_Price' to numeric, removing commas
stock_market_df['S&P_500_Price'] = stock_market_df['S&P_500_Price'].str.replace(',', '').astype(float)

# Filter relevant years for GDP data
world_gdp_df = world_gdp_df[['country_name', 'indicator_name', '2019', '2020', '2021', '2022', '2023', '2024']]

# Calculate year-over-year changes for Natural Gas Price and S&P 500 Price
stock_market_df['Natural_Gas_Price'] = pd.to_numeric(stock_market_df['Natural_Gas_Price'], errors='coerce')
stock_market_df['Natural_Gas_Price_Change'] = stock_market_df['Natural_Gas_Price'].pct_change()
stock_market_df['S&P_500_Price_Change'] = stock_market_df['S&P_500_Price'].pct_change()

# Merge datasets (example merging on year, assuming both datasets have a common column 'Year')
stock_market_df['Year'] = stock_market_df['Date'].dt.year
world_gdp_df = world_gdp_df.rename(columns={'country_name': 'Country Name', 'indicator_name': 'Indicator Name'})

# Select one country's GDP data for merging (e.g., United States)
usa_gdp = world_gdp_df[world_gdp_df['Country Name'] == 'United States']

# Transpose GDP data to match with the years
usa_gdp = usa_gdp.melt(id_vars=['Country Name', 'Indicator Name'], var_name='Year', value_name='GDP_Growth')
usa_gdp['Year'] = usa_gdp['Year'].astype(int)

# Merge the datasets
merged_df = pd.merge(stock_market_df, usa_gdp, on='Year')

# Drop NA values
merged_df = merged_df.dropna()

# Feature selection
X = merged_df[['Natural_Gas_Price_Change', 'GDP_Growth']]
y = merged_df['S&P_500_Price_Change']

# Split data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Model 1: Random Forest Regressor
rf = RandomForestRegressor(n_estimators=100, random_state=42)
rf.fit(X_train, y_train)
rf_predictions = rf.predict(X_test)

# Evaluate Random Forest Regressor
rf_mse = mean_squared_error(y_test, rf_predictions)
rf_r2 = r2_score(y_test, rf_predictions)

print(f'Random Forest Regressor MSE: {rf_mse}')
print(f'Random Forest Regressor R2: {rf_r2}')

# Model 2: Support Vector Regressor
svr = SVR(kernel='linear')
svr.fit(X_train, y_train)
svr_predictions = svr.predict(X_test)

# Evaluate Support Vector Regressor
svr_mse = mean_squared_error(y_test, svr_predictions)
svr_r2 = r2_score(y_test, svr_predictions)

print(f'Support Vector Regressor MSE: {svr_mse}')
print(f'Support Vector Regressor R2: {svr_r2}')
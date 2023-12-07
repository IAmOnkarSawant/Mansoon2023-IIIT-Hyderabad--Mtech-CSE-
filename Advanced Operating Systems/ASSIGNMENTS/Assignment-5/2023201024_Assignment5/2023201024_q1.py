from pyspark.sql import SparkSession
from pyspark.sql.functions import col
import time

start_time = time.time()
spark = SparkSession.builder.appName("Question1").getOrCreate()

data = spark.read.csv("./House_Pricing.csv", header=True, inferSchema=True)

selected_countries = ['GREATER LONDON', 'CLEVELAND', 'ESSEX']
filtered_data = data.filter(col('Country').isin(selected_countries))
result = (filtered_data.orderBy(col('Price').desc()).select('Price', 'Country').limit(2).orderBy(col('Price').asc()).collect())
ans = result[0]
print("=======================> OUTPUT OF QUESTION 1 <=======================")
print()
print("Second highest transacted value is {} which is transacted in {}.".format(ans['Price'], ans['Country']))

end_time = time.time()
execution_time = end_time - start_time
print("Execution time for Question 1: {} seconds".format(execution_time))
print()
print("======================================================================")
spark.stop()

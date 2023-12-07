from pyspark.sql import SparkSession
from pyspark.sql.functions import col
import time


st = time.time()
spark = SparkSession.builder.appName("Question2").getOrCreate()

print("=======================> OUTPUT OF QUESTION 2 <=======================")
print()
df = spark.read.csv("./House_Pricing.csv", header=True, inferSchema=True)
sec_tans = (df.groupBy('Country').count().orderBy(col('count').desc()).limit(2).collect())
ans = sec_tans[1]['Country']
print("Country with second most transactions is '{}'.\n".format(ans))


et = time.time()
exet = et - st
print("Execution time for Question 2: {} seconds".format(exet))
print()
print("======================================================================")

spark.stop()

from pyspark.sql import SparkSession
import pandas as pd
import os
import time

st = time.time()
spark = SparkSession.builder.appName("Question3").getOrCreate()


df = spark.read.csv("./House_Pricing.csv", header=True, inferSchema=True)
transaction_counts = (df.groupBy('Country').count().orderBy('count', ascending=False))

print("=======================> OUTPUT OF QUESTION 3 <======================")
print()
pandas_df = transaction_counts.toPandas()
output_file = "transaction_counts.csv"
output_dir = "./2023201024_q3/"
output_path = os.path.join(output_dir, output_file)

if not os.path.exists(output_dir):
    os.makedirs(output_dir)

pandas_df.to_csv(output_path, index=False)
et = time.time()
exet = et - st
print("Execution time: {} seconds".format(exet))
print()
print("======================================================================")

spark.stop()

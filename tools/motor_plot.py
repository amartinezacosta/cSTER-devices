# Import matplotlib and pandas
import matplotlib.pyplot as plt
import pandas as pd

# store dataframe
data = pd.read_csv("motor.csv")

# print dataframe 
print(data.head())

# Plot and store pwm_input
data.plot(x='time', y='pwm_input', kind='line')
plt.xlabel('Sample', fontsize=10, fontweight='bold')
plt.ylabel('PWM Input', fontsize=10, fontweight='bold')
plt.savefig('pwm_input.png')

# Plot and store encoder
data.plot(x='time', y='encoder', kind='line')
plt.xlabel('Sample', fontsize=10, fontweight='bold')
plt.ylabel('Encoder position', fontsize=10, fontweight='bold')
plt.savefig('encoder_position.png')
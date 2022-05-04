# Import matplotlib and pandas

import matplotlib.pyplot as plt
from numpy import require
import pandas as pd
import click

# example
# python3 motor_plot.py --file-name="motor.csv" --images="pwm.png" --images="encoder.png"

@click.command()
@click.option('--file-name', '-f', required=True, help='File Name')
@click.option('--images', '-i',multiple=True, default=['json'],help='Images Names')
def main(file_name, images):
    # store dataframe
    data = pd.read_csv(file_name)

    # print dataframe 
    print(data.head())

    if len(images) == 2:
        

        # Plot and store pwm_input
        data.plot(x='time', y='pwm_input', kind='line')
        plt.xlabel('Sample', fontsize=10, fontweight='bold')
        plt.ylabel('PWM Input', fontsize=10, fontweight='bold')
        plt.savefig(images[0])

        # Plot and store encoder
        data.plot(x='time', y='encoder', kind='line')
        plt.xlabel('Sample', fontsize=10, fontweight='bold')
        plt.ylabel('Encoder position', fontsize=10, fontweight='bold')
        plt.savefig(images[1])

if __name__=="__main__":
    main()

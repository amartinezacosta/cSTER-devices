# Import packages
import matplotlib.pyplot as plt
import pandas as pd
import click
import math

def to_rads(value:int, counts_per_rev:int)-> float:
    '''Convert input value into radians'''
    return (value / counts_per_rev) * (2 * math.pi)

def to_degrees(value:int, counts_per_rev:int)->float:
    '''Convert input value into degrees'''
    value_rads = to_rads(value, counts_per_rev)
    return (value_rads * (180.0/math.pi) ) 

# example
# python3 motor_plot.py --file-name="file.csv" --degree=1 --value=2660

@click.command()
@click.option('--file-name', '-f', required=True, help='File Name')
@click.option('--combined','-c', default=False, help='Combined graphs')
@click.option('--degree', '-d', default=False, help='Degree')
@click.option('--rads','-r', default=False, help='Radians' )
@click.option('--value', '-v', default=2660, help='Encoders count per revolution')
def main(file_name, combined, degree, rads, value):
    # store dataframe
    data = pd.read_csv(file_name)

    print(f'Filename: {file_name}, Value: {value}, '\
          f'Degrees: {degree}, Radians: {rads}, Combined: {combined}')

    # time,pwm_input,ticks,delta_ticks table names
    if 'time' and 'pwm_input' and 'delta_ticks' and 'ticks' in data.columns:

        print("Generating plots..")

        # Plot and store pwm_input
        data.plot(x='time', y='pwm_input', kind='line')
        plt.xlabel('Time', fontsize=10, fontweight='bold')
        plt.ylabel('PWM Input', fontsize=10, fontweight='bold')
        plt.savefig('pwm_with_time.png')

        data.plot(x='time', y='ticks', kind='line')
        plt.xlabel('Time', fontsize=10, fontweight='bold')
        plt.ylabel('Tick position', fontsize=10, fontweight='bold')
        plt.savefig('ticks_with_time.png')

        # Plot pwm_input input with delta
        data.plot(x='delta_ticks', y='pwm_input', kind='line')
        plt.xlabel('Delta time', fontsize=10, fontweight='bold')
        plt.ylabel('PWM Input', fontsize=10, fontweight='bold')
        plt.savefig('pwm_with_delta.png')

        # Plot ticks with delta
        data.plot(x='delta_ticks', y='ticks', kind='line')
        plt.xlabel('Delta time', fontsize=10, fontweight='bold')
        plt.ylabel('Tick position', fontsize=10, fontweight='bold')
        plt.savefig('tick_input_with_delta.png')

        if combined:
            # combined graph
            data.plot(x='delta_ticks', y=['pwm_input','ticks'], kind='line')
            plt.xlabel('Delta time', fontsize=10, fontweight='bold')
            plt.ylabel('Tick position', fontsize=10, fontweight='bold')
            plt.savefig('tick_input_with_delta_combined.png')
        if degree: # plot in degree
            data['degrees'] = data['ticks'].apply(lambda x: to_degrees(x, value))
            data.plot(x='time', y='degrees', kind='line')
            plt.xlabel('Time', fontsize=10, fontweight='bold')
            plt.ylabel('Ticks position in degrees', fontsize=10, fontweight='bold')
            plt.savefig("tick_degrees.png")
        if rads: # plot in rads
            data['rads'] = data['ticks'].apply(lambda x: to_rads(x, value))
            data.plot(x='time', y='rads', kind='line')
            plt.xlabel('Delta time', fontsize=10, fontweight='bold')
            plt.ylabel('Ticks position in rads', fontsize=10, fontweight='bold')
            plt.savefig("tick_rads.png")
    else:
        print("Dataframe does not have the proper columns names...")

if __name__=="__main__":
    main()



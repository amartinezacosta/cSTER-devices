import click
import serial
import time

@click.command()
@click.option('--port', '-p', required=True, help='Serial Port Number')
@click.option('--baudrate', '-b', default=9600, help='Serial Baudrate')
@click.option('--file-name', '-f', default='output.csv', help='File Name')
@click.option('--timeout', '-t', default=10, help='Serial loop timeout')
def main(port, baudrate, file_name, timeout):
    print("Port : %s, Baudrate : %i, File Name : %s, timeout = %i" % 
            (port, baudrate, file_name, timeout))
        
    data = []
    
    with serial.Serial(port, baudrate, timeout=1) as ser:
     
        start_time = time.time()
        exit = False
        while ((time.time() - start_time) < timeout) and not exit:
            #Attempt to read line from serial device
            line = ser.readline().decode('utf-8');
            #Check data is valid
            if(len(line) > 0):
                print(line.rstrip('\r\n'))
                #Do we exit?
                if line == 'exit':
                    exit = True
                else:
                    #Append line
                    data.append(line);

    with open(file_name, 'w') as file:
        for line in data:
            file.write(line);

if __name__=="__main__":
    main()

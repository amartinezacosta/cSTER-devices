# cSTER devices
<br />
<div align="center">
  <a href="https://github.com/amartinezacosta/cSTER-devices">
    <!-- ![](cSTER_logo.png) --> <!--Using image path in Doxyfile-->
 <img src="cSTER_logo.png" alt="Logo">
  </a>

  <h3 align="center">cSTER devices library for Cortex M4F microcontrollers</h3>

  <p align="center">
    Drivers for hardware devices using the cSTER drivers library
  </p>
</div>

[![CMake](https://github.com/amartinezacosta/cSTER-devices/actions/workflows/main.yml/badge.svg)](https://github.com/amartinezacosta/cSTER-devices/actions/workflows/main.yml)

## Description

The cSTER drivers will help you get started writing applications using device hardware such as
* [Motor with encoders](https://github.com/amartinezacosta/cSTER-devices/tree/main/motor)
* [WizFi360-PA](https://github.com/amartinezacosta/cSTER-devices/tree/main/wifi)
* [Pulse Position Modulation (PPM)](https://github.com/amartinezacosta/cSTER-devices/tree/main/ppm)
* [Servo](https://github.com/amartinezacosta/cSTER-devices/tree/main/servo)

## Getting Started

### Dependencies

* [cmake](https://cmake.org/download/)
* [GNU Arm Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)

For Windows, you will need to install make and add it to your PATH environment variable

* [Make for Windows](http://gnuwin32.sourceforge.net/packages/make.htm)


### Installing using cmake
To build the libraries navigate to the cloned folder and type the following command sequence on a terminal
```
mkdir build
cd build
cmake ..
make install
```
On Windows you need to type these set of commands on command prompt window:
```
mkdir build
cd build
cmake -DCMAKE_MAKE_PROGRAM=make.exe -G "Unix Makefiles" ..
make
```

## Help

Any advise for common problems or issues.

## Authors

Contributors names and contact info

* **Alejandro Martinez Acosta** <!---amartinezacosta@miners.utep.edu--> <br>
  [![Outlook](https://img.shields.io/badge/Microsoft_Outlook-0078D4?style=for-the-badge&logo=microsoft-outlook&logoColor=white&style=flat)](mailto:amartinezacosta@miners.utep.edu) 
  [![GitHub](https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white&style=flat)](https://github.com/amartinezacosta)
* **Jesus Minjares Martinez** <!---jminjares4@miners.utep.edu--> <br>
  [![Outlook](https://img.shields.io/badge/Microsoft_Outlook-0078D4?style=for-the-badge&logo=microsoft-outlook&logoColor=white&style=flat)](mailto:jminjares4@miners.utep.edu) 
  [![GitHub](https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white&style=flat)](https://github.com/jminjares4)


## Development

Tables of the microcontrollers and  integrated development environment compatible with the project.

### Table 1 Arm Cortex M4F Microcontrollers
| Microcontrollers | 
| :---: |
| ![Texas Instruments](https://img.shields.io/static/v1?label=&message=TM4C&labelColor=white&color=black&logoWidth=35&logo=data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAGwAAAAoCAYAAAAbrx%2B3AAAKYklEQVR42u1aA5B0ORDOzpvV%2FDNr2zv4bfNs27Zt27Zt27Zt2%2Fbd99V2159Lvdm9mdNs1euqrnlJOnlJf0mnu9%2BYgAIK6P%2BkyuLixqVqyjdyuWNIwTATUO7RmLLorNvHpn53eanqyk3N4KQAsDpjqhuKi5tNQLkPWMyYqmtHJT6%2FZUzyx2QkMsoElJuAnZDovH9Caem8tcbUALDPCFgqEhnXXFjYWRWJNKBrMTjPBJQbgJE3aK7dtypi6ieXRmePi8UmNxUWdmnbHWNTv142svedGeWxRU1uUAAYwdijq%2FlcPm%2FeUn%2F4zLLYEq7MkjXlG5j%2FlwLA9upquWTj5rpDY%2FD6LxjR8zLrFqgqX3FUNDqD9VeOjH%2BkskvXlG9o%2Fj8KALsNpo53lDocLLOed5d0KbppTPI7ld%2BgsW4vE9A%2FT3EEwhcM73nF5ctG9L5rA3bOsO7njNCkkpL5WXf1qPhHKIZYN7YsOtOWv3h4zxtRuP3Gn4rAZQMz90ZALuWfN6z7BVF0Wsbp%2BeHSEb3vTy%2BLLbZWY82urDu0p%2B36UbHiSayHx%2FiF22evzuYLfV%2BY711UUBD%2B7S%2FwNxAvcboH1BUtSF0xIv7%2BQKCROwoLew7qab2az%2Bs31e25RkP1Dulk9%2B1svtTndWXhsHdlKBTawvO8NcCrA8BbAc7v4M%2B1Du0b4vdUzzOrBAj5EF1znJR3%2BgPr%2BtGJL3hArhRwp5bHFjlEwBN2nJTmi%2FzMoRunhcOhfQgYgHvFqh4ip6uJvw5rrOfW50vfAqfes19njZGWZIyo9CXnHtHj6w%2BwUxKdD9cXFbXi%2BTc6HdVDTN3VI%2BMfppPfqrXhaDMw%2BQKGk7U46r4D%2F%2Boy5F6FSCFO4S4o%2FyT176NO02RtKH8B%2FhZj74lyufWuvfvGCD0loDtzMXMw%2Fr2Q%2BQH8C%2Fjr%2FPzwC8yHmxykostHznU2bh2b%2FOWSEb1vESCWj4i33co1NWLy2PYV7MC01LbtDcc4YP12WrLzEToi2QJGolJZD2B2oK8DngyFzgtTeTJ%2Fpe8BYk5%2FQDFlgf0rfpdwTw2BFYB%2FxxiznfZR3AD5Ye82PA8FV4Mn4H2ng9c1uUjzVZQucxuAgvn7amQsNoV1K9VXbUkgLkTs5bcrj%2Bxtv0XBOry37QamqlyZLAF7gvV4nOrTLaJi6HeH9H%2BAjq%2FchSc68gRy%2BXA4%2FDbb%2BgDzLrPbsTF27KsPHenzvpZcdkKSbUVFbVZV3inJrgcJyBr1tTvRHIE9OiBrN9bucuuY1E83jU5%2Bt2h15RoK6D8JGBS9GIp1wuNwMtyTWw%2B59%2BSkfQET9iLvQOMQgQUou3EMkf0Zz61zAfVWZr3M5WGaXFSPHpS50VllZYvrKboZATIA%2BkbLAOznqRUlC6jsPw2YwwRwZZ9hZqipg6K39mlPidlsIAAY%2Bxk5TfvbJhOn7mr3fZB9jLkEM8gohOD5WT%2FnYtOWhoMo8G8BRjcfxeFkgLUIeCHjEEDayFLyZ64J87zQ0bwT0XdZMs0hZQsLwx87HmMeTzDl6WxIPChygyuQ5%2F22vA9gv7UUFXW4sv%2F2HebQaMh9D2BPgZKflbFut9zxqHiNn6L9Y2U9kei3pshVOOPmycn9RpyUWWaQUR6yG9e6OUY6AP8yYNN8uk3RQBz9Xobs0zKPBPp8pd6lnL4N4Gy8o3GaEgN4MXmPcG0oX0xP1D28HF%2FmkTKDjBjQlB4bb7%2FDBg1BT9xkT7zsT%2BpTXPhDFi1FvS5A3gs%2BT%2Fh88D18pvMDJV8iyhxvmcetxTT%2BCPO3INzIN2jifN67EuXk9MyPfpvz1NGtxyY6kDGb5YGeZXKEGnhHgNcg04P6K4diydqKdQ%2FtbbuR%2BURx%2F7OlEVDmKRLrgM0i4oKvKHW%2BDAXPB4XuoWWaLp0bFL%2B7JXsafyF7kGsJILfpXLnQMagahrqd%2BAyAbgPfDT4Xc1mO4iZXCBM8WXba15KOCSiHiTttVwImdn4QUgBYBczEqmQfD61T2xzzOR7jbMfcXZ%2BJNQtLfULkfVlSTtN82lYR971KxillYKvtmpoSClOe9WK%2BelROTKUvMYUlfZah08FMSD%2FzHA0u4hzsPvbVorKS8hozwLqHWX2T0N2W0N1e%2BF1f1h3NADBOPnS8fXFLvaaC7pLkaQxcgPKFjFfoUrON6R9xBHpRPoNj0KGg6y1j%2FoLyB5JYfZ4ZDD6zDYO%2FBUfiDoz%2FqLjd32N%2Bm6m3J%2F0%2FJ5CO8peSoHppKhbvfUgzH2kSt1M5Z7JuPMZn7KP9wO%2FLPH%2BAI3K7yCyjMnRMbDWifJhkT7rlk9G30v9n6fOTlL%2FFeDdRz%2BhzKNdJx6hPr%2BGXOCeAvkBGJpFK0onJh8SJ1p13Kr01vbjFhd5c22W3LsndzkyC7hYuUHJ41%2BprQFsx0aoeIfqsYIT4bKWQ6sCTWRYX3qV63STiAZ5mKXYfNzzB%2B%2B6zksae7nSp%2B82JyQr5%2FU4%2BDXVZepGsijXf%2FPAnXC8tjYYR1FXf2kLHqkVA%2B360RKoPx6kZSQ82G8A%2BA39pRfoJFzA9iZJI9QmgxWxYmXXGP66MBdiyVn0V6wSIOM2nAPZUJoBxDXrK3JOUHjDbJLFdSADjiRDZX2mONbmc3wdYnrARwM72SSrnafjBOI9xpZuzzBgwmjg8TucJ00mi3PRnwIzEMmAxi5jYwW6QOQBgxgJsLfmsMQZyV8iCbuaUMgVMYqhvnVNWSAWBH%2BwPMKx%2FY4yxDn7XwzyuYT8bMN5pWOtz9rXhAGYGAIw0UbMtZCQy32W2hjrPHjAQYx7eJWqOsIDLFTDZKTuJzf%2Fd4l9Qv32mgNnMU80NoaYlC8DOo0m27zIJjn%2BmY5AWMLlLuUH5K1eCC1gTmdkZDYl4h2UIGOe5Bu9Kd%2B0CXChjwJwvwD%2FpgAKYTRF6N5jUEXQw1FxwgZkAJpn4UsgebmXKy7MFjH1R%2F4ncIUdzEzDuRH1NBiZxNDjsAxipXUAVvWQGmIow4Yz2fakHO%2FuSNWCafeDJsQALpzm%2BdWqKaCoyBEzvsALWOZtjtOz%2BN33emVBFOoBxLds6DlRjZoAJ%2BQNGivOUZAqYuP8uRXTddOjSAbabD2Cb00b7HOG1eXJUiXRfeXk6C0xSETSjVE6WgBnGJKwTN3cOzZIqRtJoedYiL7C9R6abBDBSsZ4C5gelbiDAajgFYbanuIktwJrBNg3nSU4D2DkuYOKwHUWLhMdaZ7O%2FL3OYaPwQhQJv0MtTvDFP4qev%2FTw%2FIm%2Ft3o3l4vyOpopKE9P5HmMje968%2B2QXvujERm2Wc3CgZbs9AmE5POPAUxnn6UmTeO0L3iVWMBpjpl9ivCrdaIyB8FjiJH5%2F4053Ngj5O44rrJ9X5kBmQz6LZ%2BjSeP5ByAFsCOcoluIO55vaMLFYP3OukHtc3vs53rOJSUPt%2FASvjPJYcJlVHpXONGgGQmKkFG2uZDhGEyDXTDrvGWm1jXXaIk5YMEKi%2FxapK5Ls%2Bma0BHSKaELtDaBjKYiO%2BfbQtqjKyF2Rx3dInR8vypNq9ZlvAL0odThri%2Fv8V6Qb480jie8JfI%2F5DymggAL6A7%2FPpMSyS0OKAAAAAElFTkSuQmCC) &nbsp; ![Microchip](https://img.shields.io/static/v1?label=&message=SAME&style=&color=black&logoWidth=35&labelColor=white&logo=data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAAAoCAMAAAB5EAzbAAAACXBIWXMAAAsSAAALEgHS3X78AAADAFBMVEVHcEwiHh8iHh%2FsGiMiHh%2FnGyPpGiPrGiPsGiPrGiMiHiDsGyTrGiPsGiPsGiPsGiPrGiMiHh%2FsGiTsGiPrGiPrGyMiHx%2FsGiPsGiMiHh8iHh8iHh8iHh8iHh8iHh%2FrGiPsGiMiHh8jHh8iHh8iHh8iHh%2FsGiPsGiPrGiPsGiPsGiMiHh8iHh8jHx8iHh8iHh8iHh8iHh8iHh8iHx8iHh8iHx8iHh8iHh8iHh8iHh%2FsGiPrGiPsGiPsGiPsGyPsGiTrGiPsGiTsGiPrGiPsGiPsGiPsGiPsGiPrGiTsGiPsGiPsGiMiHh8iHh8iHiAjHh8iHh8iHh8iHh8jHiAiHx8iHh8jHx8iHh8iHh8iHh8jHiAiHh8jHx8iHx8iHh8jHh8iHh8iHh8iHh8iHx8iHh8iHh8iHiAiHh8iHh8iHh8iHh8iHh%2FsGiPsGiPsGyPrGyPsGiTrGiPrGiPsGiTrGiPsGiPsGiPsGiPsGiPrGiPsGiPrGyPsGiPrGiPrGiPsGiPsGiPrGiPrGiPsGiPrGiPsGyPsGiPsGiPsGiPsGiTrGyPsGiPrGiPrGiPsGyMiHx8iHiAjHh8iHh8iHx8iHh8jHh8jHh8jHh8iHh8iHiAiHiAiHh8iHh8jHiAjHiDsGiTrGyPrGiPsGyPrGiTsGyPrGyPsGiPrGyPrGiTsGiPsGiTrGiTrGyPsGiTrGyTrGiPsGiPrGiPrGiPrGyPsGyPsGyPrGiTsGiPrGyPrGyPrGiTsGyTsGiPrGyPrGiPsGyPrGiTsGyPrGyPsGiPrGiTsGyPrGyPrGiPrGyTsGyPsGyTsGiPrGiTrGiPsGiPrGiTrGyTrGiMjHyAiHiDbGyPGGyMiHiAiHh8jHx8jHyAiHx8jHh8jHx8iHiAjHyAiHiAjHiAiHx8iHiAiHh8iHh8jHiDsGyT5HCYjHyD4HCX%2FHSf6HCbvGyT2HCUlISL0GyXzGyUkICEnIiTyGyT1HCXuGyT8HCb9HSb%2FHigmISL3HCXxGyQnIiMmIiPtGyT%2FHSZQIRKmAAAA5nRSTlMAAwIEAQEEAwECBP77%2FvwC%2FK3%2B%2B%2F79cv36qJEM0ujg%2FQ50blBzvQUbiacVLgMOH7lGwfjvq0ExWSbJt%2B9FN8%2FNdvKq9%2BRaUnL6nN40LIaf8TuLBxNYVCNKAyQ9Q7PrzqLz0P3E2LAb4jRTV8ySXvuMAq9nZfw9q%2FZsyO4LW9Um%2BSjqXdkXOiQH9MOVkyDxQHndfBYp%2B51%2FZ9oZpe68gSEUohpXToLYgCxiHoO6i6KO087HMNvJPBLphsNHytZ%2Fv3AJdeKZb98QVeDnV0lQ65SfZLNn%2BgECmQ9eYoIQjY6NFH3F9uNMKRr%2FsP0AAASCSURBVEjHlVUHUBRnFH7c3bh7letwR%2B9tpEkXBGkqVYiEg4gUASmKbQwGC%2FaoiYoNFYnpvWl67713kpiE1N272%2BscvZh%2F75whY2LYe7Ozt%2Fvv%2B773vTLvAK5nXGz20R1cNi4XIHRX%2Ftas1%2FMK%2FdGrq3gU%2FakndigsOoo0D%2BfenAEuatgAO7MJykL4iQUyhdygf%2F45wF2AI9%2FNnZS0WyDnC5FJFQfJZS4msZ4a9hRbJkUEn88n%2BHIjMfkSYIzR7vDYqFjhZ96ba0EMBH%2BGuHSEfOVWxklgsI4SyWXkRvfIJ81iQi7SLYGjOSPhTCXgELbQoBBZCrYBPGuQC5dS2Qj6KiUrZFgGDG6jPIUzhi3AZsNhKsf4rj86Y1%2FUH2IqYF%2BXwU9kfxOhcHjvLfPB%2FegJg6MEuQTYjARs14k8%2BPY82huD90c%2B8Kerh3SNHjnAJAkMlpGewzmGT%2FfROByyx96mq4eDf4H%2BSyaNwOE13VLjJ4fHHKPDhdsX29NpBgzyLcY9TDrBzRwiP4PID8mPaW82vKPf4RgBLkTocyMZaMCe0WdiOHx0Ze8bTu8Xx16gqbgQtnv087kJuHBoaCcghoixcCeukJjJcIr54kqB%2F5wMGDxOt4tO3pDhTD587NLVjy8vYjIJDzt7hT09couzqtsu6rPoprrD%2FkcY7wU2bLJ3U1lOCdlU5y4aiUMow22AQA92G8TDnQdgAxu2G7snHnVpoSBn9iKjgBDo0lDMsK5Jjw5yM6M5niVYS3kSQqlA9xBAGikgPAxdYS7sJHdYNyQWSvkItzhvrVGMtoqAjHAhCRzu0neICYTzGJ6wy6WEkBDL9Pe6tBbXm%2B0igZ%2BQ8BCLpFI%2FWYdZF3Gna4s9PdNIosUkkAnECoNOd%2F894FofkNr8jbstEyRFTpgXpu0JBRx3%2Ba8JIrdseiD8vq3pd199v65pOPSdw7qGYnZq8TnXAMdxXWvfcDFs3jwM%2B3YO9EDQAHA4UNWCtGjAjafRaHgclsaN%2FgENi8XiaIBDn7qxwI0OpaH9eA6j9UPZVAyw4OQC7U1MisPh%2FEt9jNUUCLDSaroDepWQnCCRSBIuKCVNTU2qJF5Zf0hIv9rrhBodxgRWSVCQioSqgMDBn78rKSk57oUYys%2BW%2Bpy6HGtao62FBatSrL%2FH%2Fba6vSVV26fqs0qCbL4SSb0t8Cebd9zq%2BrJYWwCA2la9xjvF5N2niplGkeEG7cozU03t1taads7Z%2FqTxCoew1NRz0c2NqrZpFDLFdLz2vOM0UevT03O%2Bobo%2B7kZtcPnlKGsxOoyynoZG0%2Fhp%2BKPGqzGkZfwMDHjNZ4VYGxq0phXJ08ksXqKpt7auHFg8RBCnVrdrl9fHVTXEl5bGfx2LCFbYiqHylG8zpJqKfNsvaLU%2BNT51f6b6pvyVFK9KHI%2F38amb%2Fv7HKTq0qnLqK4BiW3XPqqpxdXRSVDQtq%2BhYEUD0IECssrmtDZYHK4MDlIOtQTR3JQQFK5UBFRyvH4792vtL0ImAKEAe55Jb5ytP%2FnOA%2FmuQ0AD8f0Pd0IQA%2FA37nnjMw71BkQAAAABJRU5ErkJggg%3D%3D)|

### Table 2 Software Development
| **Integrated development environment (IDE)**| **Operating Systems**|
|:--- | :--- | 
|[![Code Composer Studio](https://img.shields.io/static/v1?label=&message=Code+Composer+Studio&style=flat&color=black&logo=data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACMAAAAjCAMAAAApB0NrAAAACXBIWXMAAA7zAAAO8wEcU5k6AAADAFBMVEVHcEzLAAHMAAHMAAHLAAHMAADMAAHLAAHMAADLAADMAADMAAHJBAXGDQ7LAAHMAADMAADLAAHBCw3LAADLAADBBQbMAQHPAADWAADLAADJDAvBBgbBCwzICwzKDAzKCgvLBAXHCQjLBATVAAC3NTbLAwXEERHKBAbLAADCEhPJBgfLAADJDQzLBgfJDQ3KBQfLAQLHCgvKAwXKCgq2Hx7KCAnLBATHCgrIDAyh%2F%2FjGExLAHyDLBgfLCAfLAgTLAQLLAgSf2%2BfJBgfIDQ7KBgfKBgfKBQbMAgPJBgfICgrLBAXKAwPLCAnJBgfKBQbLAwTLBQbKBAXHCQrJBgfKCgvJBwnCFxrEERHCGBrJBgfLAwPKCwy%2FISbLAgPEDQ3JCAjKBAXLAwXHCgrLAwPGCwrKAwTICwvKCgvGExTBBQbHDg%2FKAgPHCQrBCwzHCgt7t9jCISTKAwPHCQvJBwjIExSj0cHFDg%2FLAwTKBgbMCQnMBwjKBgbGAADGAADLCAnIDAzDAADJBgbHCgvKDg%2FIEhLFFRXLAgPKAwQA%2F6LJBwfJBgjFDw3LCQvDEhPJBQbGEhPLCQq6JibGFBbKAgPIDQ7JExPJBgfABgfKAwTLCQq%2FHyLHCwq9Cw7IBwihTUzFCgvLAADICArGCwvIDQ7KAgPKAwTEEBTCBAjKCAnBBAXCBAXJBwjKAwXJBAXJBwfFCwvGEBDIBgW6QlTHCgzHFhfJCAjGBwjIBwfKAwSoZXXLAwTMAAHMAAG9DxLKCQrICAjLAADCCwzBCwzBCw3LAwTICAnLAwPIDAvFCgnJCgvHCQrICAvJBQfLBAXYAAHMAADWAAHMAAHZAAHXAAHVAAHTAADUAAHPAADSAADWAALWAgPVAADXAALaAAHUAQLWAQPQAQLWAADVAQLLAAHQAADRAADPAQLYAALUAADNAADNAAHSAAHLAQPZAALaAALTAQPLAADMAQLOAAHOAADmAAHaAADRAQLZAADgAQLdAQPiAQLOAgLXAADcAADSAQLTAwVISLWdAAAAznRSTlMA%2B%2Fr7%2FPv%2B%2Fv77%2FfwDAf38%2Bvpe%2FvyQAwMB%2FWGPXQJjjskC0wIH0yC%2B%2BgaZAmKsY6%2F5N8aNCYzBY0sCJxHOzOj99gGVRIvHpuyfgrLcnJ6i5eG5SYaPexAiFpDgkAr8M3G4xFbxP8tFlCuOT%2F1aXFcBD9txc1gDO%2BbDyNbIBwTKVAW%2BUGEwHf7yAXebPqkhtC%2BYEBnuXC%2B3k9mPDGw0fgYs92Q8I%2FPiGZVdjYpu1uB0SjSgAzUTaz5k0ALX9vkmimD4WVtg81PMX0dlU2KJ3d1J1TAAAAOSSURBVDjLddQHfBNVGADw70buvbtrL4mJhajUWgsthdpSbQFBNgIyFQXBKiAyBMS9By7cdU%2BW4N574N5b73K5y2rSmKR7MkXcfpeUtLV4v9%2F9fve%2B%2B79x333vAfS8snMAbgPIGQD%2Fdw1AMer2%2FAXVAEMOro7qB7B%2B7hjVr46bejNA%2F6y%2B4miA4yfc2lQvOopa1FtKLsNYTi%2BR1R%2FgrFllvt2sk%2FpbnU5dbTz5FCvevQ68zyltV1tEjqp%2FDCzrbLGJ1Luj%2FOzxGYVjrCrcZ9RxRIrE754I98x0GpRwvJnM37YlTYbAqjkdftFGNaVh8XyrDfcVBz2E8kX1nUs3Wu1sgJULZntDDE%2BkPY8uuh97bXiuvJUShQsaS2c9kRIfvQbw1ivTwwGZl0K1D0xauejl2giVufqOKRVPAgzahL2%2B%2BOf1NwGq3t2eND2sM9jUHm1jWDGkPr35GYD5c1c%2Fi%2BYzI9Fe%2Bg7Ae2uX%2FO0VWFETnXIg%2Bv6L8wAeL37K%2B9cLaD43P9WNdDpeXdxoaGVSIrnsk8EAw05kOnZvNZ7HF%2Bd57YQREv7yNW9gmkpWd8Yrv8fw8pN2qTpDRDVt8LNdomImX3p7A6b7x28x%2BFVlPCqIVKOMei42j%2FDaiE4EIrv9TQtPOx0jBT98HTM9DBEEXRDVw7uMoLndmDSxIfrlGhj2Uzjgdgs73eJOnXYbTYiZMkc06YP9K%2BC73z6UiS5zoeguqmcM3zz6krwdYc2ls%2BrH8E3MTjSXP7rwppI%2FuW4TmQwwonAsFRy1FXDYz3aBtA4cXgXFv7Bpc4hlrr4Un%2B4yGEftsZbh264aifUw81cc59Au05w3EgbDvWrGBK6Da6%2BHqT1N5ApAM8MyR6bNCZB1DUyw5uoySvDyifiEhvVlDNb3Mr%2BcMboUjBfeCCt8KTO0xi6bV%2BLvGtug6EzaBBxU93jMcOXoNsnhOxWNTWmYU9qo6pJGixIp8%2FseTqpz8XwkJGksmmNqbJoQTFCG6gpH9j6CZt60MWrIxlMXr2iE9Z0BuTWYeIpZV8SgOu6O6lTVj7r4QqxUWdBIxhChTmLqfVMmVafq2dqOBcPzw8122VVnrRnnwv9rCzXNtqqgX3b6tMCNdv7avJhXYljMIRqe9xvTL7oA%2B2f32Mx4j7hhn%2BEMV8DQGGsmt%2BcW9BYH1J2lZ%2B59DHL3x5esG99XHDgYHnp4Gjw4eXmv46DvAVMFx%2F1X%2FAuakVjhU6Z2TQAAAABJRU5ErkJggg%3D%3D)](https://www.ti.com/tool/CCSTUDIO#downloads) | * Windows<br> * MacOS<br> * Linux |
| [![Visual Studio Code](https://img.shields.io/badge/Visual_Studio_Code-0078D4?style=flat&logo=visual%20studio%20code&logoColor=white)](https://code.visualstudio.com/download) |  * Windows<br>* MacOS<br>* Linux |
[![Keil Arm](https://img.shields.io/static/v1?label=&message=&#181;Vision&logoWidth=50&logoHeight=40&style=flat&color=white&logo=data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAFgAAAAeCAMAAACfSil3AAAACXBIWXMAAAsSAAALEgHS3X78AAADAFBMVEVHcEwAg6sAg6sAg6sAgqsACQ0Ag6sAgqoAg6sAgagAg6sAg6sAAAAAg6oAg6sAg6sAg6oAAAAAg6sAg6sAg6sAg6sAg6sAg6sAg6sAgqoAAAAAgqoAg6sAgKcAgqsAg6oAgqoAgqsAgqoAg6sAg6oAg6oAgqoAg6oAg6sAg6sAgagAgqsAAAAAg6sAg6oAgqsAgqoAgqsAg6sAgqsAg6sAg6oAAAAAg6oAAAAAAAAAg6oAg6sAg6sAgqoAgqkAg6sAAAAAg6sAAAAAAgMAg6oAg6oAgqsAgagAg6oAg6sAEBUAAAAAg6sAAAAABggAAAAAgqsAAAAAotQAAAAAAwQAg6oAAAAAgqsAg6oAgqsAg6sAg6sA%2F%2F8Ag6oAg6sAg6oAAAAAg6oAAAAAg6sAAAAAAAAAg6oAg6sAAAAAg6sAg6sABQcAAAAAAAAAAAAAgqoAAAAAg6sAg6sAAAAAAAAAAAAAAAAAAAAAg6sAg6sAg6oAgqoAg6sAgqsAg6sAg6sAg6sAAAAAgqoAAAAAgqoAAAAAgakAAAAAg6sAg6sAg6sAAAAAgqoAgqsAg6oAg6oAAAAAg6sAg6sAAAAAAAAAAAAAg6sAAAAAg6oAAAAAAAAAg6sAgqsAg6oAg6sAg6sAg6sAg6oAg6sAg6sAAAAAAAAAAAAAAAAAAAAAgqkAAAAAKTYAAAAADxQAg6sAgqsAAAAAg6sAAAAAAAAAAAAAAAAAAAAAAAAAg6sAAAAAAQIAg6sAAAAAAAAAAAAAAAAACQ0ACAsAAAAAgqsAg6oAg6sAAAAAAAAAgqsAgqoAg6oAg6oAg6sAg6sAgagAAAAAAAAAg6oAKzgAAAAAFx4AAAAAAAAAAAAA%2F%2F8AAAAAAAAAAAAAXHgACw8ACw8AAAAAAAAAg6oAgqoAg6sAirQAiLEAg6sAh7AAibMAhq8AhK0Ai7YAg6wAiLIAjLcAha4AjroAjbgAirUAk8AAhKwAkr4Aha0Aj7sAi7UAh7EAkLwAibQAhq4AlMIAibIAhrCw9e%2BAAAAA5HRSTlMACPktAgF%2BAQME%2FfsDA3EL%2FAIuyxPcafrCOwSlHQX5%2FWTkZ%2F6YQ2OXFwYPEbVB%2BhL7aqAk6%2Bm%2FyQm4UAz37RuYrtK6OJUNeqFp2hBZ9rIbgl1pA6MrFW5l16n8%2BAEK86NDIKkeTAYYB9PujycVhS%2By3Fgnm4ciysVgvTxVCuFIMlpcPlIqNZliwNzOio1L5fBOcn2eT714fBDC77q0bYHRL6yHgwg7DF5HnPkHZB1ENpGJvBw%2FzdHksHIRIXky86YgPscUxkYYdk113kk4k3B%2FjZ4NSBralVYCKJRXBjAyZhrmLMlw%2FrhfAAAGJElEQVRIx42VB1RTSRSGrxAIMWTpoqwU6YQWpAgIiAEUBKRKXYqCyCJNERDLqoDlYFuPrK6VtXdU7NjXtpbtvbf0CCQUQSy7d15CEoSj%2FieZNzPvzjd37tyZB0Ckx9IbIpYeeUMjNcqGTjppyi6lVE1QV%2Bg0Gp1Op4bQ4C30VkZqIXkJA7w32aR6RdpGjtKUV7wlGqyPdLSNHwHAAm8vR8fIxQCMebY2CjnaLkYP3b0cU2080TTQ1tF2uQs4LG6%2BXO%2BN7ZPpwNrTJRLw257yNfRfewwb3WzoaZN7FCA3wkwm4vUuBJjo0%2Fusr1OEapMtzQK42NMm5S0DOj2tv02WbQq1u2yn7FuOYO3edIAi2aSIvLyxas2MWJedhQtaIwwS%2BDpjZWdnZhBPF2cwiHpixRkpRImlZriWnLYgQyttBE8QB3Uv9YS8wJNFRbUINpb0lgGs69V9JUpTtAh4tMj8iU8BwGkpx6OvjMTOwExo%2BDjGZAKqKd0F4F0eRzDSGMEmfKZ4nCtMDHH19iah%2BUSyR76DBqe7inDj6QOyBF2tJQPgEIh%2Fac3kR00kW4hgD2GTek9fBatk3Klt07XGBXR7nDT2Xg%2FBSo8lGw20DbuZkkxtIGmFYPOnrwFjqimyTZtXC5H9Ewzgfk%2BOmqwBFm%2Boj%2BIzBaJ5wAAFmCN%2B8NChudnhg%2FloNwQ8MKc2bxHAQlnDx7CrP11FVoOZHb4NfKY1X5fylwKPtBN0PH%2F%2BvFsWDi6vA4%2FB1%2FPkabcgtb%2BMZOxgcIad5BlTkMG3VTisBEtQAvnnbwLTWBAoNQtBx3fQFWRNjzfseMmxeyxxV4XCUMAJRvly9oLlG8A45qFo3Ex0fLQltWSNGHf4htzmMTPEPmOpOUmMhWmmBuyICPacIZt3CxgsFo2lBiO5%2BWnwfAhsb8gizUFZwS4IFhsyRSYs4g6CmcLJlsNlhbl4qaU63ZRgJC%2FK9hkDdzKa8nC8BpjksXu3wM5cmkMS6XXp1uET6N7s4OBwx1MDjP89L3YD1HQtx%2FogMJ48L16GHbNvC8YUwRmS93PGE31tOujkGWK2EHW3f6AG4y%2B9fzfo1cgXkgUPgNcIY%2BzwrmBAuDRIy0OCA7KiJFoe1m1EIuFMvCv4MZxM6q7oyPTwsCIKEt9RgXHDdvZsAQMTaSDlvwJMg6Yunsw6hHTV9EulMvEYiAjul7a3d6J40jYEl73gyaXkdovq6WtXqLPrswGwHjBqekfBjCihMqkGPL4%2F1enIOjZZUEG4vVN4zhcwZ9%2BRcHv7SavsnZzswzGWjuPDJzmFkFtr6ipFv73T1HrVARnxrzweLvvaLVMeAwV4QDqgTs%2FhpTP0C0LAwJ7cGQjGMRvnK7kqj5Nv%2Fv7HzUqKzLBkMBJPWAB5YuWbRHyQTWcw3pvWihbTw%2BZCYuKN3346Bt9NIx4%2FqwXnB8JmWNS9IWSAqwTrQEls%2BXm3ewBGyp%2Fbz0oHZ60EC6WtPpxqwUZo1bYFANVJADeO5hOw1NjVV%2FAI1ovSPFVcjVBUXMLCH5QFNxlaj5FG6Fkdijwb%2F63nLpTiq6uwvRICriWA39FGctELU%2F%2B2%2BgfiZbezMEs1L3oCtoCKKxAWy0Vf4gLcwuCjE79yKw6i67HVVQlzZ0H0AkRf2lq3GcBtQYqfPwQ0ci8kbF5NwAKhrzfskl0c5tNEwJvvwaf54LbiRzdorDZqKf4ltFgfQ%2BH24bTC6QGNsYcxEud%2FSNl%2BF9z8tv8JsK00OQliD%2BHQennUDJjSt5PNdvY0VcmZtjd7CRW%2FihT%2FKoCEtXEJGMAboclQEnqQxLgSuKWl15Jw6tzCuLhtW4Ebdrf8L2g5S%2BK0AotHaa6Q80LOsX4ieKxWt7XUio1ZYQGz4uB60urClaWFq5OuQ9Xc6EPlB3C%2BllMlXCP4%2Flu08IsGOFPuj4%2Bt1XAuF%2FaD33EEzygA7y1eXps2vfOKHF2o7c%2B9CrNT1oYBrFybMhvq%2FMO%2BqiPdB0quFEMuF2v7o%2F2RXnfmcCUYHW%2FNn44bkK%2FIHdYbMt%2BIeuoMcw78VqDv6gOiox6jQx0SOmM4KeczQht9fZLE%2Bvok5jr6FMtI3wKKv7RQ5DFVUIZUSYr%2FAUMBZRG5pb67AAAAAElFTkSuQmCC)](https://www.keil.com/download/) | * Windows |
 
## Software
This project was developed in C programming language.

![C](https://img.shields.io/badge/Progamming%20Language-00599C?style=for-the-badge&logo=c&logoColor=white&style=flat)
 
## Version History

* 0.1
    * Initial Release

## License

This project is licensed under the [NAME HERE] License - see the LICENSE.md file for details

## Acknowledgments


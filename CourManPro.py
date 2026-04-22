import os
import random
from datetime import datetime
import pyfiglet
import shutil
import pygame

LI = "*---------------------------------------------------------------------------*"

def gen_ran_id():
    num = random.randint(1000, 9999)
    return f"S{num}"

def get_date_time():
    return datetime.now().strftime("%d/%m/%Y %H:%M:%S")

def clear_screen():
    os.system('cls')

class SenderDetails:
    def __init__(self):
        self.sendn = ""
        self.senmob = ""
        self.senadd = ""

class ReceiverDetails:
    def __init__(self):
        self.recn = ""
        self.recmob = ""
        self.recadd = ""

class Customer(SenderDetails, ReceiverDetails):
    def __init__(self):
        super().__init__()
        self.id = ""
        self.date_time = ""
        self.parctype = ''
        self.mod = ''
        self.deltype = ''
        self.weight = 0.0
        self.charges = 0.0

# ///////////////////////////////////////////////////////////////////////////////////////////////

def input_customer():
    c = Customer()
    print("\n\t\t\t\033[1;37m---Enter Sender's Details---")

    while True:
        c.sendn = input("\033[1;38;5;205mSender's Name :- \033[1;37m")
        if c.sendn.replace(" ", "").isalpha() and len(c.sendn) > 0:
            break
        print("\n\033[1;37mInvalid Name! Please use only letters (A-Z).\033[1;38;5;205m")
    
    while True:
        c.senmob = input("\033[1;38;5;205mSender's Mobile No :- \033[1;37m")
        if len(c.senmob) == 10:
            break
        print("\n\033[1;37mInvalid Mobile Number\n\033[1;38;5;205mAgain, ")

    c.senadd = input("\033[1;38;5;205mSender's Address :- \033[1;37m")

    print("\n\t\t\t\033[1;37m---Enter receiver's Details---")

    while True:
        c.recn = input("\033[1;38;5;205mReceiver's Name :- \033[1;37m")
        if c.recn.replace(" ", "").isalpha() and len(c.recn) > 0:
            break
        print("\n\033[1;37mInvalid Name! Please use only letters (A-Z).\033[1;38;5;205m")

    while True:
        c.recmob = input("\033[1;38;5;205mReceiver's Mobile No :- \033[1;37m")
        if len(c.recmob) == 10:
            break
        print("\n\033[1;37mInvalid Mobile Number\n\033[1;38;5;205mAgain, ")

    c.recadd = input("\033[1;38;5;205mReceiver's Address :- \033[1;37m")

    print("\n\t\t\t\033[1;37m---Enter Parcel Details---")
    
    while True:
        print("\033[1;38;5;205mParcel Type : \033[1;37m(D: Documents / E: Electronics / C: Clothes / F: Fragile) :- ", end="")
        c.parctype = input().upper()
        if c.parctype in ['D', 'E', 'C', 'F']:
            break
        print("\033[1;37mInvalid Choice, Type Again")

    while True:
        try:
            c.weight = float(input("\033[1;38;5;205mWeight (grams) :- \033[1;37m"))
            if c.weight > 0:
                break
            print("Weight must be positive.")

        except ValueError:
            print("Please enter a numeric value.")

    while True:
        print("\033[1;38;5;205mDelivery Type : \033[1;37m(N: Normal / E: Express / S: Same-day) :- ", end="")
        c.deltype = input().upper()
        if c.deltype in ['N', 'E', 'S']:
            break
        print("\033[1;37mInvalid Choice, Type Again")

    while True:
        print("\n\t\t\t\033[1;37m---Enter Payment Details---")
        c.mod = input("\033[1;38;5;205mMode : \033[1;37m(C: COD / O: Online / P: Prepaid) :- ").upper()
        if c.mod in ['C', 'O', 'P']:
            break
        print("\033[1;37mInvalid Choice, Type Again")

    parcrate = {'D': 30, 'E': 50, 'C': 40, 'F': 60}[c.parctype]
    deltypem = {'N': 1, 'E': 2, 'S': 3}[c.deltype]
    
    c.charges = c.weight * parcrate * deltypem
    c.id = gen_ran_id()
    c.date_time = get_date_time()
    
    print("\n\033[1;38;5;220mCharges calculated automatically. ID generated.")
    return c

# ///////////////////////////////////////////////////////////////////////////////////////////////

def book():
    c = input_customer()
    try:
        with open("CourManPro.txt", "a") as fp:
            fp.write(f"\nTracking ID -> {c.id}\n")
            fp.write(f"Booking Date & Time -> {c.date_time}\n")
            fp.write("\n---Sender Details---\n")
            fp.write(f"Name -> {c.sendn}\nMobile No -> {c.senmob}\nAddress -> {c.senadd}\n")
            fp.write("\n---Receiver Details---\n")
            fp.write(f"Name -> {c.recn}\nMobile No -> {c.recmob}\nAddress -> {c.recadd}\n")
            fp.write("\n---Parcel Details---\n")
            fp.write(f"Parcel Type -> {c.parctype}\nWeight (in grams) -> {c.weight}\nDelivery Type -> {c.deltype}\n")
            fp.write("\n---Payment Details---\n")
            fp.write(f"Mode -> {c.mod}\nCharges -> Rs.{c.charges}\n")
            fp.write(f"{LI}\n")
        print("\n\033[1;37mParcel Booked Successfully")
    except Exception as e:
        print(f"File Error: {e}")
    
    input("\n\033[1;92mPress Enter to Continue.......")

# ///////////////////////////////////////////////////////////////////////////////////////////////

def display():
    if not os.path.exists("CourManPro.txt") or os.stat("CourManPro.txt").st_size == 0:
        print("\n\033[1;37mNo Records found.")
    else:
        with open("CourManPro.txt", "r") as fp:
            for line in fp:
                if "->" in line:
                    parts = line.split("->")
                    print(f"\033[1;38;5;220m{parts[0]}->\033[1;37m{parts[1]}", end="")
                else:
                    print(f"\033[1;37m{line}", end="")
    
    input("\n\033[1;38;5;205mPress Enter to Continue.......")

# ///////////////////////////////////////////////////////////////////////////////////////////////

def search():
    
    while True:
        trackid = input("\n\033[1;31mEnter Tracking ID of Parcel -> \033[1;37m")
        
        if not trackid.strip():
            print("You didn't enter anything!")

        else:
            break

    search_str = f"Tracking ID -> {trackid}"
    found = False
    
    print()

    if os.path.exists("CourManPro.txt"):
        with open("CourManPro.txt", "r") as fp:
            lines = fp.readlines()
            for i, line in enumerate(lines):
                if search_str in line:
                    found = True
                    for j in range(i, len(lines)):
                        print("\033[1;32m]","\033[1;37m",lines[j], end="")
                        if LI in lines[j]:
                            break
                    break
    
    if found:
        print("\n\033[1;38;5;220mRecord Found.")
    else:
        print("\n\033[1;38;5;220mNo Record Found.")

    input("\n\033[1;38;5;205mPress Enter to Continue.......")

# ///////////////////////////////////////////////////////////////////////////////////////////////

def delete_parcel():
    trackid = input("\n\033[1;92mEnter Tracking ID to Delete -> ")
    search_str = f"Tracking ID -> {trackid}"
    found = False
    
    if os.path.exists("CourManPro.txt"):
        with open("CourManPro.txt", "r") as f_in:
            lines = f_in.readlines()
        
        with open("sampleee.txt", "w") as f_out:
            skip = False
            for line in lines:
                if search_str in line:
                    found = True
                    skip = True
                    continue

                if skip:
                    if LI in line:
                        skip = False
                    continue
                f_out.write(line)
        
        os.remove("CourManPro.txt")
        os.rename("sampleee.txt", "CourManPro.txt")
        
    if found:
        print("\n\033[1;31mRecord Deleted Successfully.")
    else:
        print("\n\033[1;31mNo Record found.")
        if os.path.exists("sampleee.txt"): os.remove("sampleee.txt")
    
    input("\n\033[1;92mPress Enter to Continue...")

# ///////////////////////////////////////////////////////////////////////////////////////////////

def update_parcel():
    print("\033[1;32m")
    record_found = False
    print("\nTo Update the record of any Parcel,")
    trackid_input = input("\n\033[1;37mEnter Tracking ID of Parcel -> \033[1;32m")

    trackid_line_format = f"Tracking ID -> {trackid_input}"

    if not os.path.exists("CourManPro.txt"):
        print("\n\033[1;37mFile Not Found!")
        return

    with open("CourManPro.txt", "r") as file, open("sampleee.txt", "w") as temp_file:
        lines = file.readlines()
        i = 0
        while i < len(lines):
            current_line = lines[i].strip()

            if current_line == trackid_line_format and not record_found:
                record_found = True
                print("\n\033[1;37mRecord found...\033[1;32m\n")

                record_block = []
                record_block.append(lines[i])
                i += 1
                
                while i < len(lines) and LI not in lines[i]:
                    record_block.append(lines[i])
                    i += 1
                
                for idx, r_line in enumerate(record_block):
                    fields = ["Name ->", "Mobile No ->", "Address ->", "Weight (in grams) ->", "Mode ->", "Delivery Type ->", "Parcel Type ->"]
                    
                    if any(field in r_line for field in fields):
                        print(f"\n\033[1;32mCurrent : \033[1;37m{r_line.strip()}")
                        choice = input("\n\033[1;37mDo you want to update this field? (y/n): ").lower()
                        
                        if choice == 'y':
                            prefix = r_line.split("->")[0]
                            while True:
                                new_val = input(f"\n\033[1;35mEnter new {prefix.strip()} -> \033[1;37m")
                                
                                if "Name" in prefix and not (new_val.replace(" ", "").isalpha() and len(new_val) > 0):
                                    print("\033[1;32mInvalid Name! Use only letters.")
                                    continue


                                if "Mobile No" in prefix and len(new_val) != 10:
                                    print("\033[1;32mInvalid Number! Must be 10 digits.")
                                    continue
                                

                                if "Parcel Type" in prefix:
                                    new_val = new_val.upper()
                                    if new_val not in ['D', 'E', 'C', 'F']:
                                        print("\033[1;32mInvalid Type! (D, E, C, or F)")
                                        continue
                    

                                if "Delivery Type" in prefix:
                                    new_val = new_val.upper()
                                    if new_val not in ['N', 'E', 'S']:
                                        print("\033[1;32mInvalid Choice! (N, E, or S)")
                                        continue

                                
                                if "Mode" in prefix:
                                    new_val = new_val.upper()
                                    if new_val not in ['C', 'O', 'P']:
                                        print("\033[1;32mInvalid Mode! (C, O, or P)")
                                        continue

                                
                                if "Weight" in prefix:
                                    try:
                                        float(new_val)
                                    except ValueError:
                                        print("\033[1;32mInvalid Weight! Please enter a number.")
                                        continue

                                
                                record_block[idx] = f"{prefix}-> {new_val}\n"
                                break

            
                weight, p_type, d_type = 0.0, '', ''
                for r_line in record_block:
                    if "->" in r_line:
                        val = r_line.split("->")[1].strip()
                        if "Weight" in r_line: weight = float(val)
                        elif "Parcel Type" in r_line: p_type = val.upper()[0] if val else 'D'
                        elif "Delivery Type" in r_line: d_type = val.upper()[0] if val else 'N'

                parcrate = {'D': 30, 'E': 50, 'C': 40, 'F': 60}.get(p_type, 30)
                deltypem = {'N': 1, 'E': 2, 'S': 3}.get(d_type, 1)
                new_charges = weight * parcrate * deltypem

                for idx, r_line in enumerate(record_block):
                    if "Charges -> Rs." in r_line:
                        record_block[idx] = f"Charges -> Rs.{new_charges}\n"
                        break

                for updated_line in record_block:
                    temp_file.write(updated_line)
                temp_file.write(LI + "\n")
            
            else:
                temp_file.write(lines[i])
            i += 1

    if record_found:
        os.remove("CourManPro.txt")
        os.rename("sampleee.txt", "CourManPro.txt")
        print("\n\033[1;37mRecord has been Updated Successfully...")
    else:
        print("\n\033[1;37mNo Record found...")
        if os.path.exists("sampleee.txt"): os.remove("sampleee.txt")

    input("\n\033[1;92mPress enter to Continue...")

# ///////////////////////////////////////////////////////////////////////////////////////////////

def calculate_charges():
    print(f"\n\033[1;92mCharges are calculated based on weight and parcel type.")
    print("\n\t\t\t\033[1;37m---Enter Parcel Details---")

    while True:
        print("\n\033[1;35mParcel Type \033[1;37m(D:Doc, E:Elec, C:Cloth, F:Fragile) :- ", end="")
        parctype2 = input().upper()
        if parctype2 in ['D', 'E', 'C', 'F']:
            break
        print("\n\033[1;37mInvalid Choice, Type Again")
            

    while True:
        try:
            weight2 = float(input("\n\033[1;35mWeight \033[1;37m(grams) \033[1;37m:- "))
            if weight2 > 0:
                break
            print("Weight must be positive.")

        except ValueError:
            print("Please enter a numeric value.")


    while True:
        print(f"\n\033[1;35mDelivery Type \033[1;37m(N:Normal, E:Express, S:Same-day) :- ", end="")
        deltype2 = input().upper()
        if deltype2 in ['N', 'E', 'S']:
            break
        print("\n\033[1;37mInvalid Choice, Type Again")

    rates = {'D': 30, 'E': 50, 'C': 40, 'F': 60}
    multipliers = {'N': 1, 'E': 2, 'S': 3}

    parcrate2 = rates.get(parctype2, 60)
    deltypem2 = multipliers.get(deltype2, 1)
    total_charges = weight2 * parcrate2 * deltypem2
    
    print(f"\n\033[1;35mTotal Charges -> \033[1;37m{total_charges}")
    input("\n\033[1;92mPress enter to Continue.......")

# ///////////////////////////////////////////////////////////////////////////////////////////////

def menu():
    while True:
        clear_screen()
        print("\033[1;33m\n   COURIER MANAGEMENT SYSTEM")
        print("==============================")
        print("1 -> \033[1;37mBook a Parcel\033[1;33m")
        print("2 -> \033[1;37mDisplay All Parcels\033[1;33m")
        print("3 -> \033[1;37mSearch Parcel by Tracking ID\033[1;33m")
        print("4 -> \033[1;37mDelete a Parcel\033[1;33m")
        print("5 -> \033[1;37mUpdate Parcel Information\033[1;33m")
        print("6 -> \033[1;37mCalculate Delivery Charges\033[1;33m")
        print("Any Key -> \033[1;37mExit")
        
        choice = input("\n\033[1;37mHere :- ")
        
        if choice == '1': book()
        elif choice == '2': display()
        elif choice == '3': search()
        elif choice == '4': delete_parcel()
        elif choice == '5': update_parcel()
        elif choice == '6': calculate_charges()
        else: break

# ///////////////////////////////////////////////////////////////////////////////////////////////

def play_music():
    filename = "Akaza_music.mp3"
    if os.path.exists(filename):
        pygame.mixer.init()
        pygame.mixer.music.load(filename)
        pygame.mixer.music.play(-1)
    else:
        print(f"File {filename} not found.")

def stop_music():
    if pygame.mixer.get_init():
        pygame.mixer.music.stop()

# ///////////////////////////////////////////////////////////////////////////////////////////////

def welcome():
    clear_screen()
    columns, _ = shutil.get_terminal_size(fallback=(160, 24))
    width = columns

    border = "\033[1;33m" + "*" * width + "\033[1;37m"
    empty_line = "\033[1;33m*" + " " * (width - 2) + "*\033[1;37m"

    subtitle = "Fast - Reliable - Efficient"
    info1 = "Manage your parcels with ease"
    info2 = "Book, Display, Search, Delete, Update and Calculate Charges"
    title_figlet = pyfiglet.figlet_format("Courier Management", font='big')

    print(border)

    for _ in range(6):
        print(empty_line)

    for line in title_figlet.splitlines():
        if line.strip():
            pad = (width - 2 - len(line)) // 2
            print(f"\033[1;33m*{' ' * pad}\033[1;33m{line}{' ' * (width - 2 - pad - len(line))}\033[1;33m*")

    print(empty_line)

    def print_centered(text, color_code="\033[1;37m"):
        padding = (width - 2 - len(text)) // 2
        print(f"\033[1;33m*{' ' * padding}{color_code}{text}{' ' * (width - 2 - padding - len(text))}\033[1;33m*")

    print_centered(subtitle, "\033[1;91m")
    print_centered(info1, "\033[1;92m")
    print_centered(info2, "\033[1;36m")

    dev_text = "Developed by Sukhman"
    dev_pad = (width - 2 - len(dev_text)) // 2
    print(f"\033[1;33m*{' ' * dev_pad}\033[1;33mDeveloped by \033[1;97mSukhman\033[1;37m{' ' * (width - 2 - dev_pad - len(dev_text))}\033[1;33m*")

    for _ in range(6):
        print(empty_line)

    print(border)
    input("\nPress Enter to Continue.......")

# ///////////////////////////////////////////////////////////////////////////////////////////////

if __name__ == "__main__":
    play_music()
    welcome()
    menu()
    stop_music()
    print("\n\n\033[1;91mExiting Program.......")
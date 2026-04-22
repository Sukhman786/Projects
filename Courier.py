import os
import random
import time
from datetime import datetime
import pyfiglet
import shutil
import winsound

# line variable
LI = "*---------------------------------------------------------------------------*"

# functions
def gen_ran_id():
    num = random.randint(1000, 9999)
    return f"S{num}"

def get_date_time():
    return datetime.now().strftime("%d/%m/%Y %H:%M:%S")

def clear_screen():
    os.system('cls' if os.name == 'nt' else 'clear')

# classes
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


def input_customer():
    c = Customer()
    print("\n\t\t\t\033[1;37m---Enter Sender's Details---")
    
    c.sendn = input("\033[1;38;5;205mSender's Name :- \033[1;37m")
    
    while True:
        c.senmob = input("\033[1;38;5;205mSender's Mobile No :- \033[1;37m")
        if len(c.senmob) == 10:
            break
        print("\n\033[1;37mInvalid Mobile Number\n\033[1;38;5;205mAgain, ")

    c.senadd = input("\033[1;38;5;205mSender's Address :- \033[1;37m")

    print("\n\t\t\t\033[1;37m---Enter receiver's Details---")
    c.recn = input("\033[1;38;5;205mReceiver's Name :- \033[1;37m")

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

    c.weight = float(input("\033[1;38;5;205mWeight (grams) :- \033[1;37m"))

    while True:
        print("\033[1;38;5;205mDelivery Type : \033[1;37m(N: Normal / E: Express / S: Same-day) :- ", end="")
        c.deltype = input().upper()
        if c.deltype in ['N', 'E', 'S']:
            break
        print("\033[1;37mInvalid Choice, Type Again")

    print("\n\t\t\t\033[1;37m---Enter Payment Details---")
    c.mod = input("\033[1;38;5;205mMode : \033[1;37m(C: COD / O: Online / P: Prepaid) :- ").upper()

    # Calculation logic
    parcrate = {'D': 30, 'E': 50, 'C': 40, 'F': 60}.get(c.parctype, 60)
    deltypem = {'N': 1, 'E': 2, 'S': 3}.get(c.deltype, 1)
    
    c.charges = c.weight * parcrate * deltypem
    c.id = gen_ran_id()
    c.date_time = get_date_time()
    
    print("\n\033[1;38;5;220mCharges calculated automatically. ID generated.")
    return c


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

def search():
    trackid = input("\n\033[1;37mEnter Tracking ID of Parcel -> ")
    search_str = f"Tracking ID -> {trackid}"
    found = False
    
    if os.path.exists("CourManPro.txt"):
        with open("CourManPro.txt", "r") as fp:
            lines = fp.readlines()
            for i, line in enumerate(lines):
                if search_str in line:
                    found = True
                    # Print until the separator line
                    for j in range(i, len(lines)):
                        print(lines[j], end="")
                        if LI in lines[j]:
                            break
                    break
    
    if found:
        print("\n\033[1;38;5;220mRecord Found.")
    else:
        print("\n\033[1;38;5;220mNo Record Found.")
    input("\n\033[1;38;5;205mPress Enter to Continue.......")


def delete_parcel():
    trackid = input("\n\033[1;37mEnter Tracking ID to Delete -> ")
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
        print("\nNo Record found.")
        if os.path.exists("sampleee.txt"): os.remove("sampleee.txt")
    
    input("\n\033[1;92mPress Enter to Continue...")


def update_parcel():
    print("\033[1;32m")
    record_found = False
    print("\nTo Update the record of any Parcel,")
    trackid_input = input("\033[1;37mEnter Tracking ID of Parcel -> \033[1;32m")

    trackid_line_format = f"Tracking ID -> {trackid_input}"
    li = "*---------------------------------------------------------------------------*"

    if not os.path.exists("CourManPro.txt"):
        print("\n\033[1;37mFile Not Found!")
        return

    # Open original file to read and a temp file to write
    with open("CourManPro.txt", "r") as file, open("sampleee.txt", "w") as temp_file:
        lines = file.readlines()
        i = 0
        while i < len(lines):
            current_line = lines[i].strip()

            # Check if this is the record we want to update
            if current_line == trackid_line_format and not record_found:
                record_found = True
                print("\n\033[1;37mRecord found...\033[1;32m\n")

                # Store the lines of this specific record
                record_block = []
                record_block.append(lines[i]) # Tracking ID line
                i += 1
                
                # Collect lines until the separator LI
                while i < len(lines) and li not in lines[i]:
                    record_block.append(lines[i])
                    i += 1
                
                # List of fields that are allowed to be updated
                fields_to_check = ["Name ->", "Mobile No ->", "Address ->", 
                                   "Weight (in grams) ->", "Mode ->", 
                                   "Delivery Type ->", "Parcel Type ->"]

                # Loop through the block to ask for updates
                for idx, r_line in enumerate(record_block):
                    if any(field in r_line for field in fields_to_check):
                        print(f"\nCurrent : {r_line.strip()}")
                        choice = input("\033[1;37mDo you want to update this field? (y/n): ").lower()
                        
                        if choice == 'y':
                            while True:
                                new_val = input("\033[1;32mEnter new value -> ")
                                # Validation for Mobile Number
                                if "Mobile No ->" in r_line and len(new_val) != 10:
                                    print("\033[1;37mInvalid Number. Must be 10 digits.")
                                    continue
                                
                                # Reconstruct the line
                                prefix = r_line.split("->")[0]
                                record_block[idx] = f"{prefix}-> {new_val}\n"
                                break

                # --- Recalculate Charges ---
                weight = 0.0
                p_type = ''
                d_type = ''

                for r_line in record_block:
                    if "->" in r_line:
                        val = r_line.split("->")[1].strip()
                        if "Weight (in grams)" in r_line: weight = float(val)
                        elif "Parcel Type" in r_line: p_type = val.upper()[0] if val else ' '
                        elif "Delivery Type" in r_line: d_type = val.upper()[0] if val else ' '

                # Rates logic
                parcrate = {'D': 30, 'E': 50, 'C': 40, 'F': 60}.get(p_type, 60)
                deltypem = {'N': 1, 'E': 2, 'S': 3}.get(d_type, 1)
                new_charges = weight * parcrate * deltypem

                # Update the charges line in the block
                for idx, r_line in enumerate(record_block):
                    if "Charges -> Rs." in r_line:
                        record_block[idx] = f"Charges -> Rs.{new_charges}\n"
                        break

                # Write the updated block to temp file
                for updated_line in record_block:
                    temp_file.write(updated_line)
                temp_file.write(li + "\n")
            
            else:
                # If not the record we want, just copy the line as is
                temp_file.write(lines[i])
            i += 1

    # Replace old file with new file
    if record_found:
        os.remove("CourManPro.txt")
        os.rename("sampleee.txt", "CourManPro.txt")
        print("\n\033[1;37mRecord of the Parcel has been Updated Successfully...")
    else:
        print("\n\033[1;37mNo Record found...")
        os.remove("sampleee.txt")

    input("\n\033[1;92mPress enter to Continue...")


def calculate_charges():
    print(f"\n\033[1;92mCharges have been Calculated automatically according to the Weight and Type of parcel")
    
    print("\n\t\t\t\033[1;37m---Enter Parcel Details---")

    # Replaces 'Goto2' label
    while True:
        print("\n\033[1;35mParcel Type : \033[1;37m(Type 'D' for Documents / 'E' for Electronics / 'C' for Clothes / 'F' for Fragile, etc.) :- ", end="")
        parctype2 = input().upper()

        if parctype2 in ['D', 'E', 'C', 'F']:
            break
        print("\n\033[1;37mInvalid Choice, Type Again \033[1;35m")
            
    print(f"\n\033[1;35mWeight of the parcel in grams :- \033[1;37m", end="")
    try:
        weight2 = float(input())
    except ValueError:
        weight2 = 0.0 # Basic error handling for non-numeric input

    # Replaces 'Goto1' label
    while True:
        print(f"\n\033[1;35mDelivery Type : \033[1;37m(Type 'N' for Normal, 'E' for Express, 'S' for Same-day) :- ", end="")
        deltype2 = input().upper()

        if deltype2 in ['N', 'E', 'S']:
            break
        print("\n\033[1;37mInvalid Choice, Type Again\033[1;35m")

    # Rates calculation using Dictionaries (Cleaner than nested if/else)
    rates = {'D': 30, 'E': 50, 'C': 40, 'F': 60}
    multipliers = {'N': 1, 'E': 2, 'S': 3}

    parcrate2 = rates.get(parctype2, 60)
    deltypem2 = multipliers.get(deltype2, 1)

    total_charges = weight2 * parcrate2 * deltypem2
    
    print(f"\n\033[1;35mTotal Charges -> \033[1;37m{total_charges}")

    print("\n\033[1;92mPress enter to Continue.......")
    input() # Works like cin.get()


def menu():
    while True:
        clear_screen()
        print("\033[1;33m\n   COURIER MANAGEMENT SYSTEM")
        print("==============================")
        print("1 -> Book a Parcel")
        print("2 -> Display All Parcels")
        print("3 -> Search Parcel by Tracking ID")
        print("4 -> Delete a Parcel")
        print("5 -> Update Parcel Information")
        print("6 -> Calculate Delivery Charges")
        print("Any Key -> Exit")
        
        choice = input("\n\033[1;37mHere :- ")
        
        if choice == '1': book()
        elif choice == '2': display()
        elif choice == '3': search()
        elif choice == '4': delete_parcel()
        elif choice == '5': update_parcel()
        elif choice == '6': calculate_charges()
        else: break

# def welcome():
#     clear_screen()
#     width = 135
#     print("\033[1;33m" + "*" * width)
#     print("*" + " " * (width-2) + "*")
#     print(f"* {'COURIER MANAGEMENT SYSTEM':^{width-4}} *")
#     print(f"* {'Developed by Sukhman':^{width-4}} *")
#     print("*" + " " * (width-2) + "*")
#     print("\033[1;33m" + "*" * width + "\033[0m")
#     input("\nPress Enter to Continue.......")

def play_music():
    """Plays background music silently using the Windows sound engine"""
    # Note: winsound only supports .wav files
    filename = "Akaza_music.wav" 
    
    if os.path.exists(filename):
        # SND_FILENAME = play a file
        # SND_ASYNC    = play in background (don't stop the code)
        # SND_LOOP     = keep repeating the song
        winsound.PlaySound(filename, winsound.SND_FILENAME | winsound.SND_ASYNC | winsound.SND_LOOP)
    else:
        print(f"\n\033[1;31mError: '{filename}' not found. Please convert your MP3 to WAV.\033[0m")

def stop_music():
    """Stops all internal Windows sounds"""
    winsound.PlaySound(None, winsound.SND_PURGE)


def welcome():
    # Clear screen (works for both Windows and Linux/Mac)
    os.system('cls' if os.name == 'nt' else 'clear')

    # Get terminal width automatically or default to 80
    columns, _ = shutil.get_terminal_size(fallback=(160, 24))
    width = columns
    
    border = "\033[1;33m" + "*" * width + "\033[0m"
    empty_line = "\033[1;33m*" + " " * (width - 2) + "*\033[0m"

    # Texts to show
    subtitle = "Fast - Reliable - Efficient"
    info1 = "Manage your parcels with ease"
    info2 = "Book, Track, Update, Search, Display and Calculate Charges"

    # Generate Figlet Title
    # 'slant' is a common figlet font, but you can leave it default
    title_figlet = pyfiglet.figlet_format("Courier Management", font='slant')

    # Print top border
    print(border)

    # Empty spacing lines
    for _ in range(3):
        print(empty_line)

    # Print Figlet Title Centered
    for line in title_figlet.splitlines():
        if line.strip():
            pad = (width - 2 - len(line)) // 2
            print(f"\033[1;33m*{' ' * pad}\033[1;92m{line}{' ' * (width - 2 - pad - len(line))}\033[1;33m*")

    print(empty_line)

    # Function to center normal text
    def print_centered(text, color_code="\033[1;37m"):
        padding = (width - 2 - len(text)) // 2
        print(f"\033[1;33m*{' ' * padding}{color_code}{text}{' ' * (width - 2 - padding - len(text))}\033[1;33m*")

    print_centered(subtitle, "\033[1;91m")
    print_centered(info1, "\033[1;92m")
    print_centered(info2, "\033[1;36m")

    # Developer line (handling the nested color for "Sukhman")
    dev_text = "Developed by Sukhman"
    dev_pad = (width - 2 - len(dev_text)) // 2
    print(f"\033[1;33m*{' ' * dev_pad}\033[1;33mDeveloped by \033[1;97mSukhman\033[0m{' ' * (width - 2 - dev_pad - len(dev_text))}\033[1;33m*")

    # Bottom spacing
    for _ in range(3):
        print(empty_line)

    print(border)

    input("\nPress Enter to Continue.......")

if __name__ == "__main__":
    play_music()
    welcome()
    menu()
    stop_music()
    print("\n\n\033[1;91mExiting Program.......")
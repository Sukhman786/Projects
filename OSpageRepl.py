import pandas as pd
from tabulate import tabulate
import os
import pygame
import pyfiglet
import shutil

# -------- LRU PAGE REPLACEMENT --------
def lru(user_input, pages, capacity):    
    frames = []
    history = []
    results = []
    faults = 0

    for p in pages:
        if p in frames:
            results.append("HIT")
            frames.remove(p)
            frames.append(p)
        else:
            results.append("FAULT")
            faults += 1
            if len(frames) < capacity:
                frames.append(p)
            else:
                frames.pop(0)
                frames.append(p)
        
        history.append(frames + ["-"] * (capacity - len(frames)))

    
    B_CYAN   = "\033[1;96m"
    B_RED    = "\033[1;91m"
    B_GREEN  = "\033[1;92m"
    B_YELLOW = "\033[1;93m"
    B_WHITE  = "\033[1;97m"
    RESET    = "\033[1;37m"

    colored_history = []
    for step in history:
        colored_step = [f"{RESET}{B_WHITE}{item}{RESET}{B_CYAN}" for item in step]
        colored_history.append(colored_step)

    df = pd.DataFrame(colored_history).transpose()
    df.index = [f"{RESET}{B_YELLOW}Slot {i+1}{RESET}{B_CYAN}" for i in range(capacity)]
    
    colored_results = []
    for r in results:
        color = B_GREEN if r == "HIT" else B_RED
        colored_results.append(f"{RESET}{color}{r}{RESET}{B_CYAN}")
    df.loc[f"{RESET}Result{RESET}{B_CYAN}"] = colored_results

    colored_headers = [f"{RESET}{B_YELLOW}{p}{RESET}{B_CYAN}" for p in pages]

    # 5. Final Print
    print(f"\n{RESET}" + "="*50)
    print(f"{B_RED}            ALGORITHM OUTPUT{RESET}")
    print("="*50)
    
    table_output = tabulate(df, headers=colored_headers, tablefmt="fancy_grid", stralign="center")
    print(B_CYAN + table_output + RESET)
    
    print(f"\n{RESET}Total Page Faults: {B_RED}{faults}{RESET}\n")


    input("\n\033[1;37mPress Enter to Continue.......")

# ///////////////////////////////////////////////////////////////////////////////////////////////

# -------- OPTIMAL PAGE REPLACEMENT --------
def optimal(user_input, pages, capacity):
    frames = []
    history = []
    results = []
    faults = 0

    for i in range(len(pages)):
        curr = pages[i]
        if curr in frames:
            results.append("HIT")
        else:
            results.append("FAULT")
            faults += 1
            if len(frames) < capacity:
                frames.append(curr)
            else:
                idx_to_replace = -1
                farthest = -1
                for j in range(len(frames)):
                    remaining = pages[i+1:]
                    if frames[j] not in remaining:
                        idx_to_replace = j
                        break
                    else:
                        if remaining.index(frames[j]) > farthest:
                            farthest = remaining.index(frames[j])
                            idx_to_replace = j
                frames[idx_to_replace] = curr
        
        history.append(frames + ["-"] * (capacity - len(frames)))


    B_CYAN   = "\033[1;96m"
    B_RED    = "\033[1;91m"
    B_GREEN  = "\033[1;92m"
    B_YELLOW = "\033[1;93m"
    B_WHITE  = "\033[1;97m"
    RESET    = "\033[1;37m"

    colored_history = []
    for step in history:
        colored_step = [f"{RESET}{B_WHITE}{item}{RESET}{B_CYAN}" for item in step]
        colored_history.append(colored_step)

    df = pd.DataFrame(colored_history).transpose()
    df.index = [f"{RESET}{B_YELLOW}Slot {i+1}{RESET}{B_CYAN}" for i in range(capacity)]
    
    colored_results = []
    for r in results:
        color = B_GREEN if r == "HIT" else B_RED
        colored_results.append(f"{RESET}{color}{r}{RESET}{B_CYAN}")
    df.loc[f"{RESET}Result{RESET}{B_CYAN}"] = colored_results

    colored_headers = [f"{RESET}{B_YELLOW}{p}{RESET}{B_CYAN}" for p in pages]

    # 5. Final Print
    print(f"\n{RESET}" + "="*50)
    print(f"{B_RED}            ALGORITHM OUTPUT{RESET}")
    print("="*50)
    
    table_output = tabulate(df, headers=colored_headers, tablefmt="fancy_grid", stralign="center")
    print(B_CYAN + table_output + RESET)
    
    print(f"\n{RESET}Total Page Faults: {B_RED}{faults}{RESET}\n")

    input("\n\033[1;37mPress Enter to Continue.......")

# ///////////////////////////////////////////////////////////////////////////////////////////////

def menu():
    while True:
        os.system('cls')
        print("\033[1;33m\n   SELECT YOUR ALGORITHM")
        print("==============================")
        print("1 -> \033[1;37mLeast Recently Used (LRU) Page Replacement\033[1;33m")
        print("2 -> \033[1;37mOptimal Page Replacement\033[1;33m")
        print("3 -> \033[1;37mBoth\033[1;33m")
        print("Any Key -> \033[1;37mExit")
        
        choice = input("\n\033[1;37mHere :- ")
        
        if choice == '1':
            user_input = input("\n\033[1;91mEnter Reference String (e.g., 7 0 1 2): \033[1;37m")
            pages = list(map(int, user_input.split()))
            capacity = int(input("\n\033[1;91mEnter Frame Capacity: \033[1;37m"))

            lru(user_input, pages, capacity)


        elif choice == '2':
            user_input = input("\n\033[1;91mEnter Reference String (e.g., 7 0 1 2): \033[1;37m")
            pages = list(map(int, user_input.split()))
            capacity = int(input("\n\033[1;91mEnter Frame Capacity: \033[1;37m"))

            optimal(user_input, pages, capacity)
        

        elif choice == '3':
            user_input = input("\n\033[1;91mEnter Reference String (e.g., 7 0 1 2): \033[1;37m")
            pages = list(map(int, user_input.split()))
            capacity = int(input("\n\033[1;91mEnter Frame Capacity: \033[1;37m"))

            lru(user_input, pages, capacity)
            optimal(user_input, pages, capacity)


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
    os.system('cls')
    columns, _ = shutil.get_terminal_size(fallback=(160, 24))
    width = columns

    border = "\033[1;33m" + "*" * width + "\033[1;37m"
    empty_line = "\033[1;33m*" + " " * (width - 2) + "*\033[1;37m"

    subtitle = "Fast - Reliable - Efficient"
    info1 = "Solve Page Replacements Algos Fastly"
    info2 = "LRU and Optimal Page Replacement Algorithms"
    title_figlet = pyfiglet.figlet_format("Page Replacement", font='big')

    print(border)

    for _ in range(5):
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

    for _ in range(5):
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
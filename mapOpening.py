import webbrowser
from urllib.parse import quote

def show_on_map(sender_addr, receiver_addr):
    
    base_url = "https://www.google.com/maps/dir/?api=1"
    origin = quote(sender_addr)
    destination = quote(receiver_addr)
    
    final_url = f"{base_url}&origin={origin}&destination={destination}"
    
    webbrowser.open(final_url)

show_on_map("Bibi Kaulan ji Bhalai kendar, Tarn Taran Road, Amritsar",
            "B-Block,Sandhu colony, G.T. Road, Chheharta, Amritsar")
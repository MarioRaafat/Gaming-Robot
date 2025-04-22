import kociemba
# Example input: scrambled cube as a 54-character string using color codes
# Let's assume standard colors:
# U = White (W), R = Red, F = Green, D = Yellow, L = Orange, B = Blue
# input sequence is white , red , blue , yellow , orange , green
# Scrambled cube (you can change this)
color_input = (
    "OYRRWGGWY"  
    "BRYORWGWO"  
    "RGRBBBBBO"  
    "WYWRYOOOY"  
    "WBWGOWGYR"  
    "GOBRGYBGY"  
)

# Map colors to face codes based on center stickers
def custom_map_colors_to_faces(color_string):
    if len(color_string) != 54:
        raise ValueError("Input must be 54 characters long.")
    # Map colors to face codes
    return color_string.replace("W", "U").replace("R", "R").replace("G", "C").replace("Y", "D").replace("O", "L").replace("B", "F").replace("C", "B")


stringToSolve = custom_map_colors_to_faces(color_input)
print("Scrambled cube string:", stringToSolve)
if (stringToSolve=="UUUUUUUUURRRRRRRRRFFFFFFFFFDDDDDDDDDLLLLLLLLLBBBBBBBBB"):
    print("The cube is already solved.")
else:
    solution = kociemba.solve(stringToSolve)
    print("Solution:", solution)

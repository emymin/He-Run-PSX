import os

filename = input("Enter image file name: ")
file = open(filename+".asm", "w") 


asmcode = """
    opt	m+,l.,c+

    section data

    global {name}_texture
{name}_texture:
    incbin '{name}.TIM'

""".format(name=filename)
file.write(asmcode)
file.close()

os.system("asmpsx /l {name}.asm,{name}.obj".format(name=filename))
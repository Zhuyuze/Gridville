import random

if __name__ == '__main__':
    fileName = input('Input filename \n')
    m = int(input('Input m \n'))
    n = int(input('Input n \n'))
    top = int(input('Input top limit for number \n'))
    bot = int(input('Input bottom limit for number \n'))
    thr = int(input('Input threshold for number \n'))
    inFile = open(fileName, 'w')
    inFile.write(str(m) + ' ' + str(n) + ' ' + str(thr) + '\n')
    for i in range(m):
        for j in range(n):
            inFile.write(str(random.randint(bot, top)) + ' ')
        inFile.write('\n')
    inFile.close()

import pandas as pd
import numpy as np
import math
import argparse

"""
loc = mean
scale = deviation

from wiki 
Taiwan male average height is 173
Taiwan female average height is 160
the male and female rate is about 98
so the average of Taiwan people is about 166


height = random.normal(loc=166, scale=5.5, size = (1, 23000000))
weight = random.normal(loc=64, sclae=8, size=(1, 23000000))

"""
def Gussian_probability(x, mean, deviation):
    x = float(x)
    mean = float(mean)
    var = float(deviation)**2
    exponent = (x-mean)**2/(var*2*-1)
    denom = deviation*math.sqrt(2*math.pi)
    return math.exp(exponent)/denom

def main():
    parser = argparse.ArgumentParser(description='fill arguement')

    parser.add_argument('--w', type=int, required=True,
                        help='input weight')

    parser.add_argument('--h', type=int, required=True,
                        help="input height")

    parser.add_argument('--i', type=float, required=True,
                        help="the probability of independence of Taiwan")

    args = parser.parse_args()

    height = args.h
    weight = args.w
    iTaiwan = args.i

    pheight = Gussian_probability(height, 166, 5.5)
    pweight = Gussian_probability(weight, 64, 8)



    print("probability of height: ",pheight)
    print("probability of wight: ",pweight)
    print(pheight*pweight*10**8*iTaiwan)

if __name__ == "__main__":
    main()



import cv2
import numpy as np
import collections 

def getColorList():
    dict = collections.defaultdict(list)
 
    # red
    lower_red = np.array([156, 43, 46])
    upper_red = np.array([180,255,255])
    color_list = []
    color_list.append(lower_red)
    color_list.append(upper_red)
    dict['red'] = color_list

    # green 
    lower_green = np.array([35, 43, 46])
    upper_green = np.array([77, 255, 255]) 
    color_list = []
    color_list.append(lower_green)
    color_list.append(upper_green) 
    dict['green'] = color_list

    return dict

# process the image and judge whether the image has more green or red areas.
def get_color(frame):
    print('go in get_color')
    hsv = cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)
    cv2.imshow('hsv.jpg',hsv)
    # print('hsv.shape',hsv.shape)
    maxsum = -100
    color = None
    color_dict = getColorList()
    for d in color_dict:
        mask = cv2.inRange(hsv,color_dict[d][0],color_dict[d][1])        
        binary = cv2.threshold(mask, 127, 255, cv2.THRESH_BINARY)[1]
        binary = cv2.dilate(binary,None,iterations=2)
        cv2.imshow(d+'.jpg', binary)
        sum = 0
        height, width = binary.shape 
        for i in range(height): 
            for j in range(width):
                if binary[i,j] == 255:
                    sum += 1
        # print('d',sum)
        if sum > maxsum :
            maxsum = sum
            color = d 
    return color
    

if __name__ == '__main__':
    frame = cv2.imread('H:/green2.jpg') # put your image here
    print(get_color(frame))
    cv2.waitKey(0)
    cv2.destroyAllWindows()
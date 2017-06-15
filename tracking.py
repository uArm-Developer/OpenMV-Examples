# Object tracking with keypoints example.
# Show the camera an object and then run the script. A set of keypoints will be extracted
# once and then tracked in the following frames. If you want a new set of keypoints re-run
# the script. NOTE: see the docs for arguments to tune find_keypoints and match_keypoints.
import sensor, time, image, utime
from pyb import UART
from pyb import LED

#initial the uarm
led = LED(2) # Green led
led.toggle()
led.on()

#set the uarm to the default position
utime.sleep_ms(3000)
uart = UART(3, 115200)
uart.write("G0 X250 Y0 Z")
uart.write("160 F10000\r\n")
utime.sleep_ms(500)
uart.write("G0 X250 Y0 Z")
uart.write("160 F10000\r\n")

utime.sleep_ms(5000)

#finish the initialization
led.off()

# Reset sensor
sensor.reset()

# Sensor settings
sensor.set_contrast(3)
sensor.set_gainceiling(16)
sensor.set_framesize(sensor.VGA)
sensor.set_windowing((320, 240))
sensor.set_pixformat(sensor.GRAYSCALE)

sensor.skip_frames(time = 200)
sensor.set_auto_gain(False, value=100)

def draw_keypoints(img, kpts):
    #print(kpts)
    #img.draw_keypoints(kpts)
    img = sensor.snapshot()
    time.sleep(1000)

kpts1 = None
# NOTE: uncomment to load a keypoints descriptor from file
#kpts1 = image.load_descriptor("/desc.orb")
#img = sensor.snapshot()
#draw_keypoints(img, kpts1)

clock = time.clock()
while (True):
    clock.tick()
    img = sensor.snapshot()
    if (kpts1 == None):
        # NOTE: By default find_keypoints returns multi-scale keypoints extracted from an image pyramid.
        kpts1 = img.find_keypoints(max_keypoints=150, threshold=20, scale_factor=1.35)
        draw_keypoints(img, kpts1)
    else:
        # NOTE: When extracting keypoints to match the first descriptor, we use normalized=True to extract
        # keypoints from the first scale only, which will match one of the scales in the first descriptor.
        kpts2 = img.find_keypoints(max_keypoints=150, threshold=10, normalized=True)
        if (kpts2):
            match = image.match_descriptor(kpts1, kpts2, threshold=85)
            if (match.count()>10):
                # If we have at least n "good matches"
                # Draw bounding rectangle and cross.
                img.draw_rectangle(match.rect())
                img.draw_cross(match.cx(), match.cy(), size=10)

            print(kpts2, "matched:%d dt:%d"%(match.count(), match.theta()))

            coords = list(match.rect())
            #print(coords)

            #convert the xyz coordinates for uarm
            delta_y = (coords[2]/2+coords[0] - 160)/20
            delta_x = (coords[3]/2+coords[1] - 120)/20

            #Gcode command, seperated the command because of the limit lenght
            final_coords = "G2204 X"+str(delta_x)
            uart.write(final_coords)
            uart.write(" Y"+str(delta_y)+" Z0")
            uart.write(" F1000\r\n")
            utime.sleep_ms(300)


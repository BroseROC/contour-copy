#include <stdio.h>
#include <libusb.h>

int main(){
	//struct usb_bus *bus;
	//struct usb_device *dev;
	libusb_init(NULL);
	//libusb_find_busses();
	//libusb_find_devices();
	struct libusb_device **deviceList;
	ssize_t deviceCount = libusb_get_device_list(NULL, &deviceList);
	printf("%d", deviceCount);
	/*for (bus = usb_busses; bus; bus = bus->next){
		for (dev = bus->devices; dev; dev = dev->next){
			printf("Trying device %s/%s\n", bus->dirname, dev->filename);
			printf("\tID_VENDOR = 0x%04x\n", dev->descriptor.idVendor);
			printf("\tID_PRODUCT = 0x%04x\n", dev->descriptor.idProduct);
		}
	}*/
}
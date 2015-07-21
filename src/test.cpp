#include <iostream>
#include <libusb.h>

using namespace std;

void printdev(libusb_device *dev);

int main(){
	libusb_context* ctx = NULL;
	libusb_device** devices;
	int r;
	r = libusb_init(&ctx);
	if(r < 0){
		cout << "Init error " << r << endl;
		return 1;
	}
	libusb_set_debug(ctx, 3);
	ssize_t deviceCount = libusb_get_device_list(ctx, &devices);
	if(deviceCount < 0){
		cout << "Error getting devices" << endl;
		return 1;
	}
	cout << deviceCount << " devices" << endl;

	struct libusb_device_descriptor desc;
	struct libusb_device* dev;
	for(ssize_t i = 0; i < deviceCount; i++){
		dev = devices[i];
		printdev(dev);
	}
	/*for (bus = usb_busses; bus; bus = bus->next){
		for (dev = bus->devices; dev; dev = dev->next){
			printf("Trying device %s/%s\n", bus->dirname, dev->filename);
			printf("\tID_VENDOR = 0x%04x\n", dev->descriptor.idVendor);
			printf("\tID_PRODUCT = 0x%04x\n", dev->descriptor.idProduct);
		}
	}*/

}
void printdev(libusb_device *dev) {
	libusb_device_descriptor desc;
	int r = libusb_get_device_descriptor(dev, &desc);
	if (r < 0) {
		cout << "failed to get device descriptor" << endl;
		return;
	}
	cout << "\tNumber of possible configurations: " << (int)desc.bNumConfigurations << endl;
	cout << "\tDevice Class: " << (int)desc.bDeviceClass << endl;
	cout << "\tVendorID: " << desc.idVendor << endl;
	cout << "\tProductID: " << desc.idProduct << endl;
	libusb_config_descriptor *config;
	libusb_get_config_descriptor(dev, 0, &config);
	cout << "\tInterfaces: " << (int)config->bNumInterfaces << endl;
	const libusb_interface *inter;
	const libusb_interface_descriptor *interdesc;
	const libusb_endpoint_descriptor *epdesc;
	for(int i = 0; i < (int)config->bNumInterfaces; i++) {
		inter = &config->interface[i];
		cout << "\t\tNumber of alternate settings: " << inter->num_altsetting << endl;
		for(int j = 0; j < inter->num_altsetting; j++) {
			interdesc = &inter->altsetting[j];
			cout << "\t\t\tInterface Number: " << (int)interdesc->bInterfaceNumber << endl;
			cout << "\t\t\tNumber of endpoints: " << (int)interdesc->bNumEndpoints << endl;
				for(int k = 0; k < (int)interdesc->bNumEndpoints; k++) {
					epdesc = &interdesc->endpoint[k];
					cout << "\t\t\t\tDescriptor Type: " << (int)epdesc->bDescriptorType << endl;
					cout << "\t\t\t\tEP Address: " << (int)epdesc->bEndpointAddress << endl;
				}
		}
	}
	cout << endl << endl << endl;
	libusb_free_config_descriptor(config);
}

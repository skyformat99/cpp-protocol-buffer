//
//  main.cpp
//  client
//
//  Created by Anthony Fiorito on 2017-09-30.
//  Copyright © 2017 Anthony Fiorito. All rights reserved.
//

#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
using namespace std;

#include "client.h"
#include "product.pb.h"

void promptUser(RFQ::ProductRequest& request) {
    
}

int main(int argc, char *argv[]) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    
    Client client = Client();
    
    try {
        u_int8_t buffer[1024];
        client.openSocket();
        client.connectToServer(2000);
        
        // Get request from the user
        RFQ::ProductRequest request;
        request.set_rfq_id(111);
        
        cout << "REQUEST FOR QUOTE\n";
        cout << "Enter Account ID: ";
        int id;
        cin >> id;
        request.set_account_id(id);
        cin.ignore(256, '\n');
        
        cout << "Enter Product Number: ";
        int product_number;
        cin >> product_number;
        request.set_product_number(product_number);
        cin.ignore(256, '\n');
        
        cout << "Enter Product Category: ";
        string product_category;
        getline(cin, product_category);
        request.set_product_category(product_category);
        
        cout << "Enter Quantity: ";
        int quantity;
        cin >> quantity;
        request.set_quantity(quantity);
        
        request.SerializeToArray(&buffer, request.ByteSize());
        
        client.sendRequest(buffer, request.ByteSize());
        
        bzero(buffer, sizeof(buffer));
        
        client.readResponse(buffer, sizeof(buffer));
        
        RFQ::ProductResponse response;
        response.ParseFromArray(buffer, sizeof(buffer));
        
        cout << "========================================================================================\n";
        
        if(response.unit_price() == 0) {
            cout << response.price_validation_period() << "\n\n";
        } else {
            cout << "Unit Price\n"
                 << "$" << response.unit_price() << "\n"
                 << "Total Cost\n"
                 << "$" << response.unit_price() * quantity << "\n"
                 << "Validation Period\n"
                 << response.price_validation_period() << "\n\n";
            
        }
        
        client.close();
    } catch(runtime_error& e) {
        cout << e.what() << endl;
    }
    
    google::protobuf::ShutdownProtobufLibrary();
    
    return 0;
}

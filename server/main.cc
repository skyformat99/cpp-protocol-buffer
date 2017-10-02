//
//  main.cpp
//  server
//
//  Created by Anthony Fiorito on 2017-09-30.
//  Copyright © 2017 Anthony Fiorito. All rights reserved.
//

#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
using namespace std;

#include "server.h"
#include "product.pb.h"

// Model
struct Product {
    int product_number;
    string product_category;
    float unit_price;
    string validation_period;
    
    Product(int product_number, string product_category, float unit_price, string validation_period): product_number(product_number), product_category(product_category), unit_price(unit_price), validation_period(validation_period) {}
};

// Loads data.csv from the main working directory.
vector<Product> loadDataStore() {
    ifstream data("data.csv");
    vector<Product> products;
    string line;
    while(getline(data, line, '\r')) {
        std::stringstream linestream(line);

        int product_number = 0;
        string product_category;
        float unit_price = 0.0;
        string validation_period;
        
        string value;
        
        while(getline(linestream, value, ',')) {
            product_number = stoi(value);
            
            getline(linestream, product_category, ',');
            
            getline(linestream, value, ',');
            unit_price = stof(value);
            
            getline(linestream, validation_period);
        }
        products.push_back(Product(product_number, product_category, unit_price, validation_period));
    }
    
    return products;
}

// finds a product by its product number
Product const& findProduct(const vector<Product>& p, const int product_number) {
    auto it = find_if(p.begin(), p.end(), [&product_number](const Product& product) {
        return product.product_number == product_number;
    });
    
    if (it != p.end()) {
        return *it;
    }
    
    throw std::runtime_error("Product Not Found.");
                      
}

int main(int argc, const char * argv[]) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    
    // initialize product database from csv file
    vector<Product> products = loadDataStore();
    
    // Initialize TCP socket server
    Server server{};
    
    try {
        u_int8_t data_buffer[1024];
        server.openSocket();
        server.listen(2000);
    
        // Continue listening and responding to message until process exits
        while (true) {
            // Read request sent from client
            RFQ::ProductRequest request;
            server.readRequest(data_buffer, sizeof(data_buffer));
        
            // deserialize request from the client
            request.ParseFromArray(data_buffer, sizeof(data_buffer));
        
            // Generate response to client
            RFQ::ProductResponse response;
        
            try {
                const Product product = findProduct(products, request.product_number());
                response.set_unit_price(product.unit_price);
                response.set_price_validation_period(product.validation_period);
            } catch(exception& e) {
                // Error checking for when user enters incorrect product number
                response.set_unit_price(0.00);
                response.set_price_validation_period("Product Not Found.");
            }
        
            // serialize response to send to client
            response.SerializeToArray(data_buffer, sizeof(data_buffer));
        
            server.sendResponse(data_buffer, response.ByteSize());
            
            bzero(data_buffer, sizeof(data_buffer));
        }
    } catch (runtime_error& e) {
        cout << e.what() << endl;
        exit(1);
    }
    
    return 0;
}

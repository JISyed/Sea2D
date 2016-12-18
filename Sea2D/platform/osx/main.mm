//
//  main.mm
//  Sea2D
//
//  Created by Jibran Syed on 4/6/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "engine/AppSys/App.hpp"

int main(int argc, const char * argv[])
{
    // Not used
    argc; argv;
    
    {
        /// Create the app that utilizing Sea2D
        sea2d::App theApp;
        
        // Run the app
        theApp.Run();
    }
    // App sould be deallocated here
        
    return 0;
}
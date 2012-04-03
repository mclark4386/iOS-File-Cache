iOS File Cache (PLACFileCache)
==============================

PLACFileCache is an iOS cache that manages storage and caching for arbitrary files (for example, images).  The cache uses a [LRU][1] caching algorithm to effectively manage the files stored.

Requirements
------------
PLACFileCache uses [ARC][2], and as such, requires a minimum target of iOS 5.  Using the callback transform methods requires blocks support.

Adding PLACFileCache to your Project
------------------------------------
Simply copy the `src/core` directory to your project.

Usage
-----

    [[PLACFileCache alloc] initWithDirectory:@"path/to/cache" maxSize:20 * kMB]; // or 20 * kKB, but that's excessively small
    
    // You can set the delegate globally or per request
    [PLACFileCache sharedCache].delegate = self;
    
The sharedCache is simply the first cache created.  You can use multiple caches:

    PLACFileCache * myCache = [[PLACFileCache alloc] initWithDirectory:@"path/to/other/cache" maxSize:20 * kMB];
    [myCache manageURL:@"http://example.com/ceilingcat.png" delegate:self];
    
If the file is not yet available, manageURL: will return nil:

    // We set the delegate globally already in this case.
    UIImage * image = [UIImage imageWithData:[[PLACFileCache sharedCache] manageURL:@"http://example.com/nyancat.gif"]];
    
    if (image) {
        // do something, otherwise wait for the delegate callback
    }

You can perform data transforms (such as image resizing, masking, cropping, etc) on the data recieved from the request:

    // Register a data transform that is run once, upon request completion.  This transform will occur before any callbacks.
    [[PLACFileCache sharedCache] registerTransform:@"transform-name" withBlock:(NSData *)^(NSData * data){
    
      NSData * yourModifiedData = [data copy];
    
      // transform the data
    
      return yourModifiedData;
    }];
    
    //  This request will store both the unmodified file (if not already saved) and the transformed file
    [[PLACFileCache sharedCache] manageURL:@"http://example.com/longcat.png" withTransform:@"transform-name" delegate:self];

Delegate Methods:

    // If any of the manage requests return nil, the cache will call the delegate upon success or failure
    - (void) fileCache:(PLACFileCache *)cache didFailWithError:(NSError *)error
    {
      // handle an error.
      // Possible errors are:
      // * Network error
      // * File access error
    }
    
    - (void) fileCache:(PLACFileCache *)cache didLoadFile:(NSData *)fileData withTransform:(NSString *)transform fromURL:(NSString *)url
    {
      // File was successfully loaded (and was not available on the manage request).
    }

Additional Modules
------------------

PLACFileCache also provides a PLACManagedImageView, which is a drop in subclass of UIImageView.  It will use the shared cache by default.

    // assuming the UIImageView was set to be an instance of PLACManagedImageView in IB
    myImageView.imageURL = @"http://example.com/sniperkitty.jpg"
    
    // assuming we defined the transform earlier
    [myOtherImageView setImageURL:@"http://example.com/boxcat.png" withTransform:@"scale-and-rotate"];
    
    // use a different cache
    myOtherImageViewIsATank.fileCache = myOtherFileCache;
    
    [myOtherImageViewIsATank setImageURL:@"http://example.com/bznscat.jpg"];
    
Since the PLACManagedImageView is a direct subclass of UIImageView, you can do anything you would with a standard UIImageView.

License
-------
This code is distributed under the terms and conditions of the MIT license.

Copyright (c) 2012 Placester, Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.



[1]: http://en.wikipedia.org/wiki/Cache_algorithms#Least_Recently_Used "Cache Algorithms: Least Recently Used"
[2]: http://developer.apple.com/library/ios/#releasenotes/ObjectiveC/RN-TransitioningToARC/Introduction/Introduction.html#//apple_ref/doc/uid/TP40011226 "Transitioning to ARC"
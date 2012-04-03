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
    
    // The sharedCache is simply the first cache created.  You can use multiple caches
    PLACFileCache * myCache = [[PLACFileCache alloc] initWithDirectory:@"path/to/other/cache" maxSize:20 * kMB];
    [myCache manageURL:@"http://example.com/ceilingcat.png" delegate:self];
    
    // If the file is not yet available, these methods will return nil
    // We set the delegate globally already in this case.
    UIImage * image = [UIImage imageWithData:[[PLACFileCache sharedCache] manageURL:@"http://example.com/nyancat.gif"]];
    
    // Register a data transform that is run once 
    [[PLACFileCache sharedCache] registerTransform:@"transform-name" withBlock:(NSData *)^(NSData * data){
    
      NSData * yourModifiedData = [data copy];
    
      // transform the data
    
      return yourModifiedData;
    }];
    
    //  This request will store both the unmodified file (if not already saved) and the transformed file
    [[PLACFileCache sharedCache] manageURL:@"http://example.com/longcat.png" withTransform:@"transform-name" delegate:self];

    // If any of the manage requests return nil, the cache will call the delegate upon success or failure
    - (void) fileCache:(PLACFileCache *)cache didFailWithError:(NSError *)error
    {
      // handle an error.
      // Possible errors are:
      // * Network error
      // * File access error
    }
    
    - (void) fileCache:(PLACFileCache *)cache didLoadFile:(NSData *)fileData fromURL:(NSString *)url
    {
      // File was successfully loaded (and was not available on the manage request).
    }

[1]: http://en.wikipedia.org/wiki/Cache_algorithms#Least_Recently_Used [Cache Algorithms: Least Recently Used]
[2]: http://developer.apple.com/library/ios/#releasenotes/ObjectiveC/RN-TransitioningToARC/Introduction/Introduction.html#//apple_ref/doc/uid/TP40011226 [Transitioning to ARC]
iOS File Cache (PLACFileCache)
==============================

PLACFileCache is an iOS cache that manages storage and caching for arbitrary files (for example, images).  The cache uses a [LRU] [1] caching algorithm to effectively manage the files stored.

Requirements
------------
PLACFileCache uses [ARC] [2], and as such, requires a minimum target of iOS 5.  Using the callback transform methods requires blocks support.

Adding PLACFileCache to your Project
------------------------------------
Simply copy the `src/core` directory to your project.

Usage
-----

    [PLACFileCache initWithDirectory:@"path/to/cache" maxSize:20 * kMB];
  
    // If the file is not yet available, these methods will return nil
    UIImage * image = [UIImage imageWithData:[[PLACFileCache sharedCache] manageURL:@"http://example.com/image.jpg" withIdentifier:@"file-identifier"]];
    [[PLACFileCache sharedCache] manageURL:@"http://example.com/image.jpg" performTransform:(NSData *)^(NSData * data){
    
      NSData * yourModifiedData = [data copy];
    
      // transform the data
    
      return yourModifiedData;
    }];
  
    NSData * file = [[PLACFileCache sharedCache] getFileWithIdentifier:@"file-identifier"];
    NSData * file = [[PLACFileCache sharedCache] getFileWithURL:@"http://example.com/image.jpg"];


  [1]: http://en.wikipedia.org/wiki/Cache_algorithms#Least_Recently_Used [Cache Algorithms: Least Recently Used]
  [2]: http://developer.apple.com/library/ios/#releasenotes/ObjectiveC/RN-TransitioningToARC/Introduction/Introduction.html#//apple_ref/doc/uid/TP40011226 [Transitioning to ARC]
//
//  PLACFileCache.h
//
//  Copyright © 2012 Placester, Inc. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#import <Foundation/Foundation.h>

@class PLACFileCache;

@protocol PLACFileCacheDelegate

- (void) fileCache:(PLACFileCache *)cache didFailWithError:(NSError *)error;

- (void) fileCache:(PLACFileCache *)cache didLoadFile:(NSData *)fileData withTransform:(NSString *)transformIdentifier fromURL:(NSString *)url;

@end

@interface PLACFileCache : NSObject

@property (weak, nonatomic) id <PLACFileCacheDelegate> delegate;

// Setting this to YES will disable fetching entirely.
@property (getter=isActive) bool active;

// Returns the shared cache.
// The shared cache is simply the first initialized cache.
+ (PLACFileCache *)sharedCache;

- (id) initWithDirectory:(NSString *)directory maxSize:(NSUInteger)size;

- (NSData *)manageURL:(NSString *)url;
- (NSData *)manageURL:(NSString *)url delegate:(id <PLACFileCacheDelegate>)delegate;

- (NSData *)manageURL:(NSString *)url withTransform:(id)transformIdentifier;
- (NSData *)manageURL:(NSString *)url withTransform:(id)transformIdentifier delegate:(id <PLACFileCacheDelegate>)delegate;

- (void)registerTransform:(id)transformIdentifier withBlock:(NSData * (^) (NSData * data))block;

- (void)clearCache;

- (NSUInteger) currentSize;
@end
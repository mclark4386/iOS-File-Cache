//
//  PLACManagedImageView.m
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

#import "PLACManagedImageView.h"

@interface PLACManagedImageView ()

@end

@implementation PLACManagedImageView

@synthesize imageURL;
@synthesize defaultImage;
@synthesize missingImage;
@synthesize fileCache;
@synthesize transformIdentifier;

- (id) initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
      self.fileCache = [PLACFileCache sharedCache];
      self.transformIdentifier = nil;
    }
    return self;
}


- (void) fetchImage
{
  NSData * data = [self.fileCache manageURL:self.imageURL withTransform:self.transformIdentifier delegate:self];
  if (data)
  {
    self.image = [UIImage imageWithData:data];
    [self setNeedsDisplay];
  }
}

- (void) fileCache:(PLACFileCache *)cache didFailWithError:(NSError *)error
{
  self.image = self.missingImage;
  [self setNeedsDisplay];
}

- (void) fileCache:(PLACFileCache *)cache didLoadFile:(NSData *)fileData withTransform:(NSString *)transformIdentifier fromURL:(NSString *)url
{
  if ([self.imageURL isEqualToString:url]) {
    self.image = [UIImage imageWithData:fileData];
    [self setNeedsDisplay];
  }
}

@end

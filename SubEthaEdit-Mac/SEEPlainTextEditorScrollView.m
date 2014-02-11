//
//  SEEPlainTextEditorScrollView.m
//  SubEthaEdit
//
//  Created by Dominik Wagner on Thu Apr 15 2004.
//  Recreated by Michael Ehrmannn on Tue Jan 21 2014
//
//  Copyright (c) 2004 - 2014 TheCodingMonkeys. All rights reserved.
//

#import "SEEPlainTextEditorScrollView.h"

#if !__has_feature(objc_arc)
#error ARC must be enabled!
#endif

void * const SEEScrollViewOverlayObservingContext = (void *)&SEEScrollViewOverlayObservingContext;

@implementation SEEPlainTextEditorScrollView

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
		[self installKVO];
    }
    return self;
}

- (id)initWithCoder:(NSCoder *)coder
{
    self = [super initWithCoder:coder];
    if (self) {
		[self installKVO];
    }
    return self;
}

- (void)dealloc
{
	[self removeKVO];
}

- (void)installKVO {
	[self addObserver:self forKeyPath:@"topOverlayHeight" options:0 context:SEEScrollViewOverlayObservingContext];
	[self addObserver:self forKeyPath:@"bottomOverlayHeight" options:0 context:SEEScrollViewOverlayObservingContext];
}

- (void)removeKVO {
	[self removeObserver:self forKeyPath:@"topOverlayHeight" context:SEEScrollViewOverlayObservingContext];
	[self removeObserver:self forKeyPath:@"bottomOverlayHeight" context:SEEScrollViewOverlayObservingContext];
}

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context
{
    if (context == SEEScrollViewOverlayObservingContext) {
		[self tile];
		[self updateTrackingAreas];
    } else {
        [super observeValueForKeyPath:keyPath ofObject:object change:change context:context];
    }
}

- (void)tile {
    // Let the superclass do most of the work.
    [super tile];

    if ([self hasVerticalScroller]) {
        NSScroller *verticalScroller = self.verticalScroller;
        NSRect verticalScrollerFrame = verticalScroller.frame;

        verticalScrollerFrame.size.height -= self.topOverlayHeight + self.bottomOverlayHeight;
        verticalScrollerFrame.origin.y    += self.topOverlayHeight;

        verticalScroller.frame = verticalScrollerFrame;
    }

	if ([self hasHorizontalScroller]) {
		NSScroller *horizontalScroller = self.horizontalScroller;
		NSRect horizontalScrollerFrame = horizontalScroller.frame;

		horizontalScrollerFrame.origin.y -= self.bottomOverlayHeight;
		horizontalScroller.frame = horizontalScrollerFrame;
	}
}


- (void)setTopOverlayHeightNumber:(NSNumber *)heightNumber {
	self.topOverlayHeight = heightNumber.doubleValue;
}

- (void)setBottomOverlayHeightNumber:(NSNumber *)heightNumber {
	self.bottomOverlayHeight = heightNumber.doubleValue;
}

@end

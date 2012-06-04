//
//  SFTabViewTestAppDelegate.h
//  SFTabViewTest
//
//  Created by Dillon on 5/31/12.
//  Copyright 2012 Dillon Aumiller. All rights reserved.
//
//==================================================================================================================================
#import <Cocoa/Cocoa.h>
#import "SFTabView.h"
#import "SFTabViewDelegate.h"
//==================================================================================================================================
@interface SFTabViewTestAppDelegate : NSObject <NSApplicationDelegate, SFTabViewDelegate>
{
  NSWindow  *window;
  SFTabView *tabView;
}
//----------------------------------------------------------------------------------------------------------------------------------
@property (nonatomic, assign) IBOutlet NSWindow  *window;
@property (nonatomic, retain) IBOutlet SFTabView *tabView;
//----------------------------------------------------------------------------------------------------------------------------------
- (IBAction) tabView_Add   :(id)sender;
- (IBAction) tabView_Close :(id)sender;
- (IBAction) tabView_Next  :(id)sender;
- (IBAction) tabView_Prev  :(id)sender;
@end

//
//  SFTabViewTestAppDelegate.m
//  SFTabViewTest
//
//  Created by Dillon on 5/31/12.
//  Copyright 2012 Dillon Aumiller. All rights reserved.
//
//==================================================================================================================================
#import "SFTabViewTestAppDelegate.h"
//==================================================================================================================================
@implementation SFTabViewTestAppDelegate
@synthesize window;
@synthesize tabView;
//----------------------------------------------------------------------------------------------------------------------------------
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
  tabView.tabOffset = -15;
  tabView.tabMinWidth = 128.0;
  tabView.tabAutoSize = YES;
  [tabView addNewTabWithTitle:@"Tab One"];
  [tabView addNewTabWithTitle:@"Tab Two"];
  [tabView addNewTabWithTitle:@"A Longer, 3rd Tab Here"];
}
//----------------------------------------------------------------------------------------------------------------------------------
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender
{
  return YES;
}
//----------------------------------------------------------------------------------------------------------------------------------
- (IBAction)tabView_Add:(id)sender
{
  [tabView addNewTab];
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
- (IBAction)tabView_Close:(id)sender
{
  if([tabView numberOfTabs] > 0)
    [tabView removeTab:[tabView selectedTab]];
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
- (IBAction)tabView_Next:(id)sender
{
  [tabView selectNextTab:self];
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
- (IBAction)tabView_Prev:(id)sender
{
  [tabView selectPreviousTab:self];
}
//----------------------------------------------------------------------------------------------------------------------------------
- (void)dealloc
{
  self.tabView = nil;
  [super dealloc];
}

@end

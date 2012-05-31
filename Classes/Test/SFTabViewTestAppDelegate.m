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
  tabView.tabAutoSize = YES;
  [tabView addTabWithRepresentedObject:[NSDictionary dictionaryWithObjectsAndKeys:@"Tab One",@"name",nil]];
  [tabView addTabWithRepresentedObject:[NSDictionary dictionaryWithObjectsAndKeys:@"Tab Two",@"name",nil]];
  [tabView addTabWithRepresentedObject:[NSDictionary dictionaryWithObjectsAndKeys:@"Some Long Tab Name Here",@"name",nil]];
}
//----------------------------------------------------------------------------------------------------------------------------------
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender
{
  return YES;
}
//----------------------------------------------------------------------------------------------------------------------------------
- (IBAction)tabView_Add:(id)sender
{
  [tabView addTabWithRepresentedObject:[NSDictionary dictionaryWithObjectsAndKeys:@"New Tab", @"name", nil]];
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

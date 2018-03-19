/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import javax.security.auth.kerberos.KerberosKey;

import junit.framework.TestCase;





/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {
	
	private boolean printStatus = false;
	private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.
	
	public UrlValidatorTest(String testName) {
		super(testName);
	}
	
	
	
	public void testManualTest()
	{
		System.out.println("MANUAL TEST\n");
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		
		System.out.println("http://www.amazon.com expected = true, actual = " + urlVal.isValid("http://www.amazon.com"));
		assertTrue(urlVal.isValid("http://www.amazon.com"));
		System.out.println("ftp://access.engr.oregonstate.edu expected = true, actual = " + urlVal.isValid("ftp://access.engr.oregonstate.edu"));
		assertTrue(urlVal.isValid("ftp://access.engr.oregonstate.edu"));
		System.out.println("http://12345.com expected = true, actual = " + urlVal.isValid("http://12345.com"));
		assertTrue(urlVal.isValid("http://12345.com"));
		System.out.println("asdf expected = false, actual = " + urlVal.isValid("asdf"));
		assertTrue(!urlVal.isValid("asdf"));
		System.out.println("http://1234 expected = false, actual = " + urlVal.isValid("http://1234"));
		assertTrue(!urlVal.isValid("http://1234"));
		System.out.println("http://books expected = false, actual = " + urlVal.isValid("http://books"));
		assertTrue(!urlVal.isValid("http://books"));
		System.out.println("http://127.0.0.1 expected = true, actual = " + urlVal.isValid("http://127.0.0.1"));
		assertTrue(urlVal.isValid("http://127.0.0.1"));
		System.out.println("http://www.google.com:80 expected = true, actual = " + urlVal.isValid("http://www.google.com:80"));
		assertTrue(urlVal.isValid("http://www.google.com:80"));
		System.out.println("http://127.0.0.1:8080 expected = true, actual = " + urlVal.isValid("http://127.0.0.1:8080/"));			// returns false, unexpected
		//assertTrue(urlVal.isValid("http://127.0.0.1:8080")); //assertion fails, see bug report #1
	}
	
	
	public void testIsValid()
	{
		// http://www.iana.org/assignments/uri-schemes/uri-schemes.xhtml
		ResultPair schemes[] = {
			new ResultPair("http",true),
			new ResultPair("aaa",true),
			new ResultPair("ftp",true),
			new ResultPair("sftps",true),
			new ResultPair("about",true),
			new ResultPair("sieve",true),
			new ResultPair("rtsp",true),
			new ResultPair("cap",true),
			new ResultPair("aaas",true),
			new ResultPair("https",true),
		};
		ResultPair domains[] = {
			new ResultPair("yahoo",true),
			new ResultPair("www.;//??::",false),
			new ResultPair("www.!",false),
			new ResultPair("@",false),
			new ResultPair(",",false),
			new ResultPair("#",false),
			new ResultPair("$",false),
			new ResultPair("()",false),
			new ResultPair("www.google",true)
		};
		ResultPair authority[] = {
			new ResultPair(".com",true),
			new ResultPair(".org",true),
			new ResultPair(".edu!",false),
			/*new ResultPair(".com?age=1",true), //assertion fails, see bug report #2*/
			new ResultPair(".com:80",true),
			new ResultPair(":asdf",false),
			
		};
		// loop thru all arrays and generate tests
		StringBuffer buffer = new StringBuffer();
		boolean expectedScheme = true, expectedDomain = true, expectedAuthority = true, expected = true, actual = true;
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		for(int i = 0; i < schemes.length ; i++){
			buffer.append(schemes[i].item);
			expected &= schemes[i].valid;
			expectedScheme = schemes[i].valid;
			int j;
			for(j = 0; j < domains.length; j++){
				buffer.append("://");
				buffer.append(domains[j].item);
				expected &= domains[j].valid;
				expectedDomain = domains[j].valid;
				int k;
				for(k = 0; k < authority.length; k++){
					buffer.append(authority[k].item);
					expected &= authority[k].valid;
					actual = urlVal.isValid(buffer.toString());
					System.out.println("URL: '" + buffer.toString() + "' expected = " + expected + " actual = " + actual);
					assertEquals(expected,actual);
					expected = expectedDomain;
					buffer.setLength(buffer.length() - authority[k].item.length());
				}
				buffer.setLength(buffer.length() - domains[j].item.length() - 3);
				expected = expectedScheme;
			}
			buffer.setLength(0);
			expected = true;
		}
		
	}
	
	//   public void testIPAddrs()
	//   {
	//	   System.out.println("Testing IP Addresses");
	//	   for (int i = 1 ; i < 512 ; ++i){
	//		   for(int j = 1 ; j < 512 ; ++j){
	//			   for(int k = 1; k < 512 ; ++k){
	//				   for(int l = 1; l < 512 ; ++l){
	//					   for(int port = 1; port < 100 ; ++port){
	//						   StringBuffer buffer = new StringBuffer();
	//						   buffer.append("http://");
	//						   buffer.append(Integer.toString(i));
	//						   buffer.append(".");
	//						   buffer.append(Integer.toString(j));
	//						   buffer.append(".");
	//						   buffer.append(Integer.toString(k));
	//						   buffer.append(".");
	//						   buffer.append(Integer.toString(l));
	//						   buffer.append(":");
	//						   buffer.append(Integer.toString(port));
	//					       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	//				    	   System.out.println("URL: '" + buffer.toString() + "' valid = " + urlVal.isValid(buffer.toString()));
	//
	//					       if (!urlVal.isValid(buffer.toString())){
	//					    	   System.out.println("URL: '" + buffer.toString() + "' valid = " + urlVal.isValid(buffer.toString()));
	//					    	   break;
	//					       }
	//					   }
	//				   }
	//			   }
	//		   }
	//	   }
	//   }
	
	
	public void testIsValid2() {
		int i, j, k, l, m, n;
		String url;
		boolean validurl;
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		
		boolean resultExpected;
		boolean result;
		for(i = 0; i < schemes.length; i++) {
			for(j = 0; j < hosts.length; j++) {
				for(k = 0; k < ports.length; k++) {
					for(l = 0; l < paths.length; l++) {
						for(m = 0; m < queries.length; m++) {
							for(n = 0; n < strings.length; n++) {
								validurl = true;
								url = schemes[i].item + hosts[j].item + ports[k].item + paths[l].item + queries[m].item + strings[n].item;
								
								if( !schemes[i].valid || !hosts[j].valid || !ports[k].valid || !paths[l].valid || !queries[m].valid || !strings[n].valid){
									validurl = false;
								}
								
								if( validurl == true){
									
									if(!urlVal.isValid(url)){
										System.out.println("FAILED: URL = '" + url + "' expected = valid, actual = invalid");
									}
									else{
										System.out.println("PASSED: URL= '" + url + "' expected = valid, actual = valid");
									}
									
								}
								else if( validurl == false){
									
									if(!urlVal.isValid(url)){
										System.out.println("PASSED: URL = '" + url + "' expected = invalid, actual = invalid");
									}
									else{
										System.out.println("FAILED: URL= '" + url + "' expected = invalid, actual = valid");
									}
									
								}
							}
						}
					}
				}
			}
		}
	}
	
	/**
	 * Create set of tests by taking the testUrlXXX arrays and
	 * running through all possible permutations of their combinations.
	 *
	 * @param testObjects Used to create a url.
	 */
	
	ResultPair[] schemes = {
	new ResultPair("http://", true),
	new ResultPair("https://", true),
	new ResultPair("ftp://", true),
	new ResultPair("sftp://", false),
	new ResultPair("http:/", false),
	new ResultPair("http:///", false),
	new ResultPair("httppp://", false),
	new ResultPair("abc", false),
	new ResultPair("://", false)
	};
	
	ResultPair[] hosts = {
	new ResultPair("www.google.com", true),
	new ResultPair("google", false),
	new ResultPair("googlegoogle.com", true),
	new ResultPair("baidu.com", true),
	new ResultPair("amazon", false),
	new ResultPair("192.168.1.1", true),
	new ResultPair("256.256.256.256", false),
	new ResultPair("", false),
	new ResultPair("^%&!@&*((", false),
	new ResultPair("", false)
	};
	
	ResultPair[] ports = {
	new ResultPair("", true),
	new ResultPair(":8080", true),
	new ResultPair(":80", true),
	new ResultPair(":65535", true),
	new ResultPair(":65536", false),
	new ResultPair(":9999999", false),
	new ResultPair(":abc", false),
	new ResultPair(":&!@%#&", false)
	};
	
	ResultPair[] paths = {
	new ResultPair("/path1", true),
	new ResultPair("/path2/", true),
	new ResultPair("/path3/path3", true),
	new ResultPair("", true),
	new ResultPair("abc", false),
	new ResultPair("!@!@&*#", false)
	};
	
	ResultPair[] queries = {
	new ResultPair("", true),
	new ResultPair("?a=123&b=456", true),
	new ResultPair("?a=123b=456", false),
	new ResultPair("abc", false),
	new ResultPair("?===", false)
	};
	
	ResultPair[] strings = {
	new ResultPair("", true),
	new ResultPair("#apog2h5u6uh4u3672", true),
	new ResultPair("#®aogh", false)
	};
	
	
}

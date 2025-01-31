#pragma once


namespace xml
{



   class document;


   class CLASS_DECL_AQUA node :
      virtual public ::data::node
   {
   protected:


      friend class ::xml::document;


      // name and value
      //string                  m_strName;
      //string                  m_strValue;

      //node *                  m_pnodeParent;      // parent node
      //node::array             m_nodea;            // children pointer node array
      //e_node                  m_etype;            // node type
      ::xml::document *          m_pdocument;             // document
      //property_set            m_set;


      node();
      node(::xml::node * pnodeParent);


   public:


      
      virtual ~node();



      inline __pointer(::xml::document) get_document() { return m_pdocument; }
      inline const __pointer(::xml::document) get_document() const { return m_pdocument; }


      virtual void set_name(const ::string & strName);
      virtual void set_value(const ::string & strValue);

      virtual void get_name(string & strName) const { strName = m_strName; }
      virtual void get_value(string & strValue) const { strValue = m_strValue; }

      inline string get_name() const { return m_strName; }
      inline string get_value() const { return m_strValue; }

   
      virtual ::xml::document* get_xml_document() const;


      index get_index() const;



      virtual index find(node * pnode);
      virtual index find(const char * pcszName, index iStart = 0);

      virtual index find(const char * pcszName, const property_set & set, index iStart = 0);

      //virtual bool contains(const property_set & set) const;
      virtual node * get_next_sibling();

      virtual node * first_child();




      // Load/Save XML
      const char *   load(const char * pszXml, parse_info * pi = nullptr);
      const char *   _load(const char * pszXml, const char * pszEndXml, parse_info * pi = nullptr);

      string get_xml(disp_option * opt = nullptr) const;
      string get_text(disp_option * opt = nullptr) const;

      bool consume(const char * & pszXml, const char * psz);
      bool consume_whitespaces(const char * & pszXml, i32 iMinimumCount = 1);

      const char * LoadOtherNodes(bool* pbRet, const char * pszXml, parse_info * pparseinfo = nullptr);

      // internal load functions
      const char *   LoadAttributes( const char * pszAttrs, parse_info * pi = nullptr);
      const char *   LoadAttributes( const char * pszAttrs, const char * pszEnd, parse_info * pi = nullptr);
      const char *   LoadProcessingInstruction( const char * pszXml, parse_info * pi = nullptr);
      const char *   LoadDocType( const char * pszXml, parse_info * pi = nullptr);
      const char *   LoadComment( const char * pszXml, parse_info * pi = nullptr);
      const char *   LoadCDATA( const char * pszXml, parse_info * pi = nullptr);

      
      node *                  get_child( const char * name);
      node *                  get_child_with_attribute(const char * pcszName, const ::id & idAttribute, const ::payload & varAttribute, index iStart = 0);

      string                  get_simple_path() const;
      index_array             get_indexed_path() const;
      void                    get_indexed_path(index_array & iaPath) const;
      node *                  get_node_from_simple_path(const char * path);
      node *                  get_node_from_indexed_path(const index_array & ia);
      node *                  get_node_from_attr_path(const char * path, const char * lpszName, const char * pszAttr);
      index_array             get_child_indexed_path(const node * pnode) const;
      void                    get_child_indexed_path(index_array & iaPath, const node * pnode) const;
      string                  get_child_simple_path(const node * pnode) const;
      string                  get_child_simple_attr_path(node * pnode, const char * pszAttr);
      node *                  get_child(const char * name, index & iStartPosition);
      string                  get_child_value(const char * name);
      string                  get_child_text(const char * name, disp_option * opt = nullptr);

      node::array             children(const char * name);
      node::array &           children();

      ::property *            GetChildAttr(const char * name, const char * attrname);
      string                  GetChildAttrValue(const char * name, const char * attrname);
      node *                  GetChildByAttr(const char * lpszName, const char * pszAttrName, const char * pszAttrValue);
      node *                  GetChildByAnyAttr(const char * lpszName, string_array & straName, string_array & straAttrValue);
      node *                  GetChildByAllAttr(const char * lpszName, string_array & straName, string_array & straAttrValue);

      node * get_child_at( index iIndex);
      node * get_child_at(const char * lpszName, index iIndex, index iDepth = 0);
      node * get_child_at_grow(const char* lpszName, index iIndex);
      ::count get_child_attr_value(string_array & stra, const char * lpszName, const char * pszAttrName, index iDepth = 1);
      ::count erase_child_with_attr(const char * lpszName, const char * pszAttrName, index iIndex, ::count iCount = 1, index iDepth = 1);

      // search node
      node *                  rfind( const char * name, i32 iDepth = -1);
      node *                  rfind(const char * pcszName, const property_set & set, index iDepth = -1);


      // modify DOM
      ::count get_children_count();
      ::count get_children_count(const char * lpszName);
      ::count get_children_count(const char * lpszName, index iDepth);
      node *                  child_at(index i);
      //node *                create_node( const char * name = nullptr, const char * value = nullptr );
      node *                  add_child(const char * name = nullptr, const char * value = nullptr);
      node *                  add_child(const char * name, const property_set & set, const char * value = nullptr);
      node *                  add_child( node * node );
      bool                    erase_child( node * node );
      node *                  detach_child( node * node );

      // node/branch copy
      void                    CopyNode( node * node );
      void                    CopyBranch( node * branch );
      void                    _CopyBranch( node * node );
      node *                  AppendChildBranch( node * node );

      bool contains(const ::property_set & set) const { return m_set.contains(set); }
      
      ::property *            find_attribute(const ::id & id) { return m_set.find_property(id); }

      template < typename TYPE >
      bool find_attribute(const ::id & id, TYPE & t) { return m_set.find(id, t); }

      ::property              attribute(const ::id & id) { return m_set[id]; }
      ::property *            attribute_at(index i) { return m_set.element_at(i); }
      ::property *            set_attribute(const property & property) { return set_attribute(property.m_id, property); }
      ::property *            set_attribute(const ::id & id, const ::payload & payload = ::e_type_new);
      bool                    erase_attribute(::property * pproperty) { return erase_attribute(pproperty->m_id); }
      bool                    erase_attribute(const ::id & id) { return m_set.erase_by_name(id) > 0; }


      bool from_row_column_v2(const string2a & str2a);
      bool to_row_column_v2(string2a & str2a);

      // operator overloads
      node * operator [] ( i32 i ) { return child_at(i); }


      void close();


      virtual ::stream & write(::stream & stream) const;
      virtual ::stream & read(::stream & stream);

   private:

      node & operator = (const node & node);
      node(const node & node);

   };

} // namespace xml

#ifndef DIP_NODE_IMPORT_H
#define DIP_NODE_IMPORT_H

namespace snt::dip {

  class ImportNode : public BaseNode {
  public:
    static BaseNode::PointerType is_node(Parser& parser);
    ImportNode(Parser& parser) : BaseNode(parser, NodeDtype::Import) {};
    BaseNode::NodeListType parse(Environment& env) override;
  };

} // namespace snt::dip

#endif // DIP_NODE_IMPORT_H
